<?php

class access_sys
{
	public static function access($page)
	{
		if( preg_match("/^https?:/", $page) )
			return true;
		if( strlen($page) > 1 )
			$page = rtrim($page, "/");
		
		$a = array();
		
		$a['/admin'] = array('ACCESS', 'USER_SELECT');
		$a['/admin/index'] = array('ACCESS', 'USER_SELECT');
		$a['/admin/group'] = array('ACCESS', 'GROUP_SELECT');
		$a['/admin/group/index'] = array('ACCESS', 'GROUP_SELECT');
		
		$a['/panel'] = array('ACCESS');
		$a['/panel/index'] = array('ACCESS');
		$a['/panel/domain'] = array('ACCESS');
		$a['/panel/domain/add'] = array('ACCESS');
		$a['/panel/profile'] = array('ACCESS');
		$a['/panel/service'] = array('ACCESS');
		$a['/panel/service/add'] = array('ACCESS');
		$a['/panel/user'] = array('ACCESS');
		$a['/panel/user/add'] = array('ACCESS');
		$a['/logout'] = array('ACCESS');
		
		if( !is_array($page) )
			$page = array($page);
		foreach( $page as $p )
		{
			if( isset($a[$p]) )
			{
				foreach( $a[$p] as $g )
					if( !security::hasGrant($g) )
						return false;
			}
		}
		
		return true;
	}
}

class security_sys extends security
{
	public function login($user='', $pass='', $save=false)
	{
		if( $user == 'admin' )
			throw new SiteException('Invalid creditentials', 403, "Invalid username : {$user}");
		
		if( !preg_match("/^[a-fA-F0-9]{32}$/", $pass) )
		{
			// this is a password so get a list of tokens
			$tokens = api::send('self/token/list', array('auth'=>'', 'user'=>$user, 'pass'=>$pass));
			
			if( count($tokens) < 1 )
				throw new SiteException("Forbidden", 403, "No available token");

			if( !$GLOBALS['CONFIG']['FORCE_FIRST_TOKEN'] )
			{
				// redirect to the login page
				foreach( $tokens as $t )
					$_SESSION['LOGIN_TOKENS'][] = array('token'=>$t['token'], 'name'=>$t['name']);
				$_SESSION['LOGIN_USER'] = $user;

				template::redirect($GLOBALS['CONFIG']['LOGIN_PAGE']);
			}
			else
			{
				// force login with the first token
				$pass = $tokens[0]['token'];
			}
		}
		
		// if reaching here, it means the $pass is a real token
		// so proceed to real authentication
		$this->directLogin($user.':'.$pass);
		
		if( $save )
			$this->save();
		
		if( isset($_SESSION['LOGIN_REDIRECT']) )
		{
			$r = $_SESSION['LOGIN_REDIRECT'];
			template::redirect($r);
		}
		else
			template::redirect($GLOBALS['CONFIG']['PANEL_PAGE']);
	}
	
	public function directLogin($auth)
	{
		security::set('API_AUTH', $auth);
		security::set('USER', preg_replace("/:.*$/s", "", $auth));
		$this->loadGrants();
	}
	
	public function loadGrants()
	{
		security::clearGrant();
		
		$grants = api::send('self/token/grant/list');

		foreach( $grants as $g )
			security::setGrant($g['name']);	
	}
	
	public function logout()
	{
		parent::logout();
		
		if( isset($_COOKIE['SYSPIE']) )
			setcookie('SYSPIE', '', time()-60*60*24*30, '/');
	}
	
	private function save($auth=null)
	{
		if( $auth == null )
			$auth = security::get('API_AUTH');
			
		$crypt = '';
		for( $i = 0; $i < strlen($auth); $i++ )
			$crypt .= base_convert(ord($auth[$i]), 10, 36);
		
		setcookie('SYSPIE', base64_encode($crypt), mktime(0,0,0,12,31,2030), '/');
	}
	
	private function load()
	{
		if( !isset($_COOKIE['SYSPIE']) )
			return null;
		
		$crypt = base64_decode($_COOKIE['SYSPIE']);
		$auth = '';
		for( $i = 0; $i < strlen($crypt); $i += 2 )
			$auth .= chr(base_convert(substr($crypt,$i,2), 36, 10));
		
		$this->directLogin($auth);
	}
	
	public function hasAccess($page)
	{
		if( !access_sys::access($page) )
		{
			// load cookie if the user is not logged yet
			if( !access_sys::access('/') )
			{
				$this->load();
				return access_sys::access($page);
			}
			else
				return false;
		}
		return true;
	}
	
	public function requireAccess($page)
	{
		if( !$this->hasAccess($page) )
			throw new SiteException('Unsufficient permission', 403, 'Not all grants available to see page : ' . $page);
	}
}

?>