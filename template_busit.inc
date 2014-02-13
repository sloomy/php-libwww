<?php

class template_busit extends template
{
	public function __construct()
	{
		$GLOBALS['lang']->import($GLOBALS['CONFIG']['CLASSPATH'] . '/template_busit.lang');
	}
	
	public function error($e)
	{
		$e = $e.'';
		preg_match("/^(.*?)(\\s*Stack trace:\\s*(.*?)\\s*(#.*)?)?$/s", $e, $matches);
		$message = $matches[1];
		
		if( count($matches) > 2 )
			$detail = $matches[3];
		else
			$detail = null;

		if( count($matches) > 3 )
			$stack = $matches[4];
		else $stack = null;

		$_SESSION['MESSAGE']['TYPE'] = 'error';
		$_SESSION['MESSAGE']['TEXT'] = "<p>".nl2br($message)."</p><strong>".nl2br($detail)."</strong>";
		
		if( $stack != null )
		{
			$stack = preg_replace("/^#+[0-9\\-]* (.+)$/m", "<li>\$1</li>", $stack);
			$stack = preg_replace("/(\\{main\\}<\\/li>.)/s", "\$1</ol><ol style=\"border-left: 2px solid #E18B7C; margin-top: 10px; margin-bottom: 20px; padding-left: 20px; list-style: decimal inside;\">", $stack);
		}
		
		$this->output();
	}
	
	public function top()
	{
		$top = "
<!DOCTYPE html>
<html xmlns='http://www.w3.org/1999/xhtml' xmlns:v=\"urn:schemas-microsoft-com:vml\">
	<head>
		<title>{$GLOBALS['lang']['TITLE']}</title>
		<meta name=\"description\" content=\"{$GLOBALS['lang']['DESCRIPTION']}\" />
		<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />
		<meta http-equiv=\"Cache-control\" content=\"no-cache\">
		<meta http-equiv=\"Expires\" content=\"-1\">
		<meta name=\"viewport\" content=\"width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no\">
		<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\">
		<meta name=\"HandheldFriendly\" content=\"true\">
		<meta name=\"google-site-verification\" content=\"0XKifQ42rWCTlPU-3fLlDjqnHqJl40o01bY2-S9D56Y\" />
		<link rel=\"shortcut icon\" href=\"/{$GLOBALS['CONFIG']['SITE']}/images/favicon.ico\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/main.css\" type=\"text/css\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/jquery/jquery-ui-1.10.3.custom.css\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/jquery/default.css\" />
		<link href=\"https://fonts.googleapis.com/css?family=Cuprum\" rel=\"stylesheet\" type=\"text/css\" />
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-1.9.1.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-ui-1.10.3.custom.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-ui-touch-punch.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-ui-timepicker.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-chartjs.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-raty.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-jsplumb.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-sceditor.bbcode.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-toggles.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/footer.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/main.js\"></script>";

if( strstr($GLOBALS['CONFIG']['PAGE'], 'panel/space/view') !== false )
	$top .= "<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/view.js\"></script>";
if( strstr($GLOBALS['CONFIG']['PAGE'], 'showcase') !== false || strstr($GLOBALS['CONFIG']['PAGE'], 'learn') !== false || strstr($GLOBALS['CONFIG']['PAGE'], 'setup') !== false )
	$top .= "<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/showcase.js\"></script>";
if( strstr($GLOBALS['CONFIG']['PAGE'], 'doc') !== false )
	$top .= "<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/doc.js\"></script>";
if( strstr($GLOBALS['CONFIG']['PAGE'], 'store') !== false )
	$top .= "<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/store.js\"></script>";
	
	$top .= "
	</head>
	<body>
	<div id=\"fb-root\"></div>
	<script>
		(function(d, s, id){
			var js, fjs = d.getElementsByTagName(s)[0];
			if (d.getElementById(id)) return;
			js = d.createElement(s); js.id = id;
			js.src = \"//connect.facebook.net/en_US/all.js#xfbml=1&appId=233857746673934\";
			fjs.parentNode.insertBefore(js, fjs);
		}(document, 'script', 'facebook-jssdk'));
	</script>
	<div id=\"wrapper\" ".((strstr($GLOBALS['CONFIG']['PAGE'], 'store') !== false && strstr($GLOBALS['CONFIG']['PAGE'], 'connector') === false)?"style=\"background-color: #e5e5e5;\"":"").">
		<div id=\"loading\"></div>
		<div class=\"header\">
			<div class=\"content\">";
		
		if( strstr($GLOBALS['CONFIG']['PAGE'], 'default') === false )
		{
			$top .="
				<div class=\"logo\">
					<a href=\"/\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/logo.png\" alt=\"logo\" /></a>
				</div>
			";
		}
		else
		{
			$top .= "
				<div class=\"logo-big\">
					<img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/logo-big.png\" alt=\"logo\" />
				</div>
			";
		}
		
	if( !$GLOBALS['CONFIG']['INSTANCE'] )	
		$top .= $this->getMainMenu();
			
		$top .= "
			</div>
		</div>
		<div class=\"core\" id=\"core\" style=\"".(strstr($GLOBALS['CONFIG']['PAGE'], 'status')!==false?"background-color: #f0f0f0;":"")."\">";
	
		$logged = $GLOBALS['security']->hasAccess('/panel');

		if( strstr($GLOBALS['CONFIG']['PAGE'], 'store') !== false || strstr($GLOBALS['CONFIG']['PAGE'], 'panel') !== false || strstr($GLOBALS['CONFIG']['PAGE'], 'admin') !== false  )
		{
			$top .= $this->getSubMenu();
		}
		
		return $top;
	}

	public function topSimple()
	{
		$GLOBALS['lang']->import($GLOBALS['CONFIG']['CLASSPATH'] . '/template_busit.lang');
		
		$top = "
<!DOCTYPE html>
<html xmlns='http://www.w3.org/1999/xhtml' xmlns:v=\"urn:schemas-microsoft-com:vml\">
	<head>
		<title>{$GLOBALS['lang']['TITLE']}</title>
		<meta name=\"description\" content=\"{$GLOBALS['lang']['DESCRIPTION']}\" />
		<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />
		<meta http-equiv=\"Cache-control\" content=\"no-cache\">
		<meta http-equiv=\"Expires\" content=\"-1\">
		<meta name=\"viewport\" content=\"width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no\">
		<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\">
		<meta name=\"HandheldFriendly\" content=\"true\">
		<meta name=\"google-site-verification\" content=\"0XKifQ42rWCTlPU-3fLlDjqnHqJl40o01bY2-S9D56Y\" />
		<link rel=\"shortcut icon\" href=\"/{$GLOBALS['CONFIG']['SITE']}/images/favicon.ico\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/main.css\" type=\"text/css\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/jquery/jquery-ui-1.10.3.custom.css\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/jquery/default.css\" />
		<link href=\"https://fonts.googleapis.com/css?family=Cuprum\" rel=\"stylesheet\" type=\"text/css\" />
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-1.9.1.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-ui-1.10.3.custom.js\"></script>
	</head>
	<body>
		<div style=\"padding: 20px;\">";
		
		return $top;
	}
	
	private function getMainMenu()
	{
		if( strstr($GLOBALS['CONFIG']['PAGE'], 'default') === false )
		{
			$menu_file = $GLOBALS['CONFIG']['ROOT'].$GLOBALS['CONFIG']['SITE'].'/mainmenu.inc';
			if( file_exists($menu_file) )
			{
				$menu_data = include_once($menu_file);
				$menu = "
				<div class=\"menu\">
						<ul>";

				$logged = $GLOBALS['security']->hasAccess('/panel');
				foreach( $menu_data as $menu_item )
				{
					// check if the user has access to the target link
					$a = $GLOBALS['security']->hasAccess($menu_item['link']);
					if( ($menu_item['anonymous'] && !$logged) || (!$menu_item['anonymous'] && $a) )
					{
						$active = '';
						if( strpos(rtrim($GLOBALS['CONFIG']['PAGE'], '/'), rtrim($menu_item['link'], '/')) === 0 )
						//if( preg_match('!^'.rtrim($menu_item['link'], '/').'(/index)?$!', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
							$active = "class=\"active\"";
						
						if( !$logged && !$menu_item['anonymous'] )
							continue;
						else
						{
							if( is_array($menu_item['sub']) )
							{
								$menu .= "
									<li class=\"{$menu_item['text']}\">
										<a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\" title=\"\" {$active}>{$GLOBALS['lang'][$menu_item['text']]}</a>
										<ul>";
									foreach( $menu_item['sub'] as $menu_subitem )
									{
										if( strpos(rtrim($GLOBALS['CONFIG']['PAGE'], '/'), rtrim($menu_subitem['link'], '/')) === 0 )
										//if( preg_match('!^'.rtrim($menu_subitem['link'], '/').'(/index)?$!', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
											$subactive = "class=\"active\"";
						
										$menu .= "
												<li class=\"{$menu_subitem['text']}\"><a id=\"link-{$menu_subitem['text']}\" href=\"{$menu_subitem['link']}\" onclick=\"{$menu_subitem['onclick']}\" title=\"\" {$subactive}>{$GLOBALS['lang'][$menu_subitem['text']]}</a></li>";
									}
									
									$menu .= "
										</ul>
									</li>";
							}
							else
							{
								$menu .= "
							<li class=\"{$menu_item['text']}\"><a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\" title=\"\" {$active}>{$GLOBALS['lang'][$menu_item['text']]}</a></li>";
							}
						}
					}
				}
				
				$menu .= "
						</ul>
					</div>
				";
				
				return $menu;
			}
			else
				return "";
		}
	}
	
	private function getSubMenu()
	{
		$menu_file = null;
		$path = $GLOBALS['CONFIG']['PATH'];
		while( strlen($path) > strlen($GLOBALS['CONFIG']['ROOT'])-2 )
		{
			if( file_exists($path.'/submenu.inc') )
			{
				$menu_file = $path.'/submenu.inc';
				break;
			}
			else
				$path = dirname($path);
		}
		
		if( $menu_file != null )
		{
			$menu_data = include_once($menu_file);
			$menu = "
					<div class=\"menu-fixed\">
						<div class=\"container\">
							<ul id=\"menu\">
			";
			
			// check which submenu is active
			$active = null;
			foreach( $menu_data as $menu_item )
			{
				// check if the user has access to the target link
				if( $GLOBALS['security']->hasAccess($menu_item['link']) )
				{
					if( strpos(rtrim($GLOBALS['CONFIG']['PAGE'], '/'), rtrim($menu_item['link'], '/')) === 0 )
					//if( preg_match('!^'.rtrim($menu_item['link'], '/').'(/index)?$!', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
						$active = $menu_item['link'];
				}
			}
			
			foreach( $menu_data as $menu_item )
			{
				// check if the user has access to the target link
				if( $GLOBALS['security']->hasAccess($menu_item['link']) )
				{
					$a = '';
					if( $active == $menu_item['link'] || ($active === null && $menu_item['default'] == true) )
						$a = "class=\"active\"";

					if( is_array($menu_item['sub']) )
					{
						$menu .= "<li id=\"".($menu_item['id']?"{$menu_item['id']}":"{$menu_item['text']}")."\" class=\"sub ".($menu_item['id']?"{$menu_item['id']}":"{$menu_item['text']}")."\"><a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\" title=\"\" {$active}>".($GLOBALS['lang'][$menu_item['text']]?"{$GLOBALS['lang'][$menu_item['text']]}":"{$menu_item['text']}")."</a>
							<ul>";
								
						foreach( $menu_item['sub'] as $menu_subitem )
						{
							if( strpos(rtrim($GLOBALS['CONFIG']['PAGE'], '/'), rtrim($menu_subitem['link'], '/')) === 0 )
							//if( preg_match('!^'.rtrim($menu_subitem['link'], '/').'(/index)?$!', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
								$subactive = "class=\"active\"";
						
							$menu .= "
								<li class=\"{$menu_subitem['text']}\"><a id=\"link-{$menu_subitem['text']}\" href=\"{$menu_subitem['link']}\"  onclick=\"{$menu_subitem['onclick']}\" title=\"\" {$subactive}>".($GLOBALS['lang'][$menu_subitem['text']]?"{$GLOBALS['lang'][$menu_subitem['text']]}":"{$menu_subitem['text']}")."</a></li>";
						}
									
						$menu .= "
							</ul>
						</li>";
					}
					else
					{
						$menu .= "
									<li id=\"".($menu_item['id']?"{$menu_item['id']}":"{$menu_item['text']}")."\" class=\"{$menu_item['text']}\"><a {$a} id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\">".($GLOBALS['lang'][$menu_item['text']]?"{$GLOBALS['lang'][$menu_item['text']]}":"{$menu_item['text']}")."</a></li>
						";
					}
				}
			}
			
			if( strstr($GLOBALS['CONFIG']['PAGE'], 'store') !== false )
			{
				$menu .= "
									<li id=\"search-li\" class=\"search\"><form id=\"searchform\"><input type=\"submit\" style=\"display: none;\" /><input class=\"auto\" style=\"width: 220px; font-size: 15px;\" type=\"text\" id=\"search\" value=\"{$GLOBALS['lang']['search']}\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['search']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['search']}' : this.value; this.value=='{$GLOBALS['lang']['search']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\" /></form></li>";
			}

			if( strstr($GLOBALS['CONFIG']['PAGE'], 'panel') !== false )
			{
				$quota = api::send('self/system/quota/user/select');
				$quota = $quota[0];
				$menu .= "
									<li style=\"float: right;\"><a href=\"/panel/credits\" id=\"credits\">{$GLOBALS['lang']['left']} {$quota['quota_used']} BIC</a></li>";
			}
			
			$menu .= "
								</ul>
							</div>
					</div>";
			
			return $menu;
		}
		else
			return "";
	}
	
	public function bottom()
	{
		$bottom = "";

		
		$bottom .= "	
		</div>
		";
		$bottom .= $this->getObjects();
		
		$bottom .= "

		<div id=\"footer\" class=\"footer\">
			<div class=\"content\">
				<ul>
					<li><a href=\"/about\">{$GLOBALS['lang']['ABOUT']}</a></li>
					<li><a href=\"/about/contact\">{$GLOBALS['lang']['CONTACT']}</a></li>
					<li><a href=\"/about/team\">{$GLOBALS['lang']['TEAM']}</a></li>
					<li><a href=\"/developers\">{$GLOBALS['lang']['DEVELOPERS']}</a></li>
					<li><a href=\"/about/legal\">{$GLOBALS['lang']['LEGAL']}</a></li>
					<li><a href=\"/status\">{$GLOBALS['lang']['STATUS']}</a></li>
				</ul>
				<p style=\"padding: 5px 0 0 0; font-size: 12px;\">
	";
	$request = str_replace(array('?lang='.translator::getLanguage(), '&lang='.translator::getLanguage()) , array('', ''), $_SERVER['REQUEST_URI']);

	$bottom .= "	
					".(translator::getLanguage()=='EN'?"<span style=\"color: #4d4d4d;\">":"<a href=\"{$request}".(strstr($request,'?')===false?"?":"&")."lang=EN\">")."English".(translator::getLanguage()=='EN'?"</span>":"</a>")."&nbsp;&nbsp;&nbsp;
					".(translator::getLanguage()=='FR'?"<span style=\"color: #4d4d4d;\">":"<a href=\"{$request}".(strstr($request,'?')===false?"?":"&")."lang=FR\">")."Fran&ccedil;ais".(translator::getLanguage()=='FR'?"</span>":"</a>")."&nbsp;&nbsp;&nbsp;
					".(translator::getLanguage()=='ES'?"<span style=\"color: #4d4d4d;\">":"<a href=\"{$request}".(strstr($request,'?')===false?"?":"&")."lang=ES\">")."Espa&ntilde;ol".(translator::getLanguage()=='ES'?"</span>":"</a>")."&nbsp;&nbsp;&nbsp;
				</p>
				<p>{$GLOBALS['lang']['COPYRIGHT']}</p>
			</div>
		</div>
	</div>
	<script type=\"text/javascript\">
	  var _paq = _paq || [];
	  _paq.push([\"trackPageView\"]);
	  _paq.push([\"enableLinkTracking\"]);

	  (function() {
		var u=((\"https:\" == document.location.protocol) ? \"https\" : \"http\") + \"://stats.anotherservice.com/\";
		_paq.push([\"setTrackerUrl\", u+\"piwik.php\"]);
		_paq.push([\"setSiteId\", \"9\"]);
		var d=document, g=d.createElement(\"script\"), s=d.getElementsByTagName(\"script\")[0]; g.type=\"text/javascript\";
		g.defer=true; g.async=true; g.src=u+\"piwik.js\"; s.parentNode.insertBefore(g,s);
	  })();
	</script>
	</body>
</html>";
		
		return $bottom;
	}
	
	public function bottomSimple()
	{
		$bottom = "
		</div>
	</body>
</html>";
		
		return $bottom;
	}
	
	private function getObjects()
	{
		if( !isset($_SESSION['ANTISPAM']) )
			$_SESSION['ANTISPAM'] = md5(time().'busit');

		$objects = "
			<div id=\"login\" class=\"floatingdialog\">
				<div class=\"form-small\">
					<h3 class=\"center\">{$GLOBALS['lang']['login']}</h3>
					<form action=\"/login_action\" method=\"post\" class=\"center\">
						<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
						<fieldset>
							<input class=\"auto\" type=\"text\" value=\"{$GLOBALS['lang']['username']}\" name=\"username\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['username']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['username']}' : this.value; this.value=='{$GLOBALS['lang']['username']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\" />
						</fieldset>
						<fieldset>
							<input class=\"auto\" type=\"password\" value=\"{$GLOBALS['lang']['password']}\" name=\"password\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['password']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['password']}' : this.value; this.value=='{$GLOBALS['lang']['password']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\"/>
							".(isset($_GET['elogin'])?"<span class=\"help-block\" style=\"color: #bc0000;\">{$GLOBALS['lang']['auth']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['register']}</span>")."
						</fieldset>						
						<fieldset>
							<input type=\"checkbox\" name=\"chbox\" />
							<label for=\"remember\" style=\"display: inline-block; padding-left: 10px;\">{$GLOBALS['lang']['remember']}</label>
						</fieldset>
						<fieldset>
							<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['login']}\" />
						</fieldset>													
					</form>
					<div class=\"clearfix\">&nbsp;</div>
				</div>
			</div>
			<div id=\"login-base\" style=\"display: none;\" class=\"floatingdialog\">
				<div class=\"form-small\">
					<h3 class=\"center\">{$GLOBALS['lang']['login']}</h3>
					<form action=\"/login_action\" method=\"post\" class=\"center\">
						<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
						<fieldset>
							<input class=\"auto\" type=\"text\" value=\"{$GLOBALS['lang']['username']}\" name=\"username\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['username']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['username']}' : this.value; this.value=='{$GLOBALS['lang']['username']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\" />
						</fieldset>
						<fieldset>
							<input class=\"auto\" type=\"password\" value=\"{$GLOBALS['lang']['password']}\" name=\"password\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['password']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['password']}' : this.value; this.value=='{$GLOBALS['lang']['password']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\"/>
							".(isset($_GET['elogin'])?"<span class=\"help-block\" style=\"color: #bc0000;\">{$GLOBALS['lang']['auth']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['register']}</span>")."
						</fieldset>						
						<fieldset>
							<input type=\"checkbox\" name=\"chbox\" />
							<label for=\"remember\" style=\"display: inline-block; padding-left: 10px;\">{$GLOBALS['lang']['remember']}</label>
						</fieldset>
						<fieldset>
							<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['login']}\" />
						</fieldset>													
					</form>
					<div class=\"clearfix\">&nbsp;</div>
				</div>
			</div>
			<div id=\"recovery\" style=\"display: none;\" class=\"floatingdialog\">
				<div class=\"form-small\">
					<h3 class=\"center\">{$GLOBALS['lang']['recovery']}</h3>
					<form action=\"/recovery_action\" method=\"post\" class=\"center\">
						<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
						<fieldset>
							<input class=\"auto\" type=\"text\" value=\"{$GLOBALS['lang']['username']}\" name=\"username\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['username']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['username']}' : this.value; this.value=='{$GLOBALS['lang']['username']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\" />
							".(isset($_GET['erecovery'])?"<span class=\"help-block\" style=\"color: #bc0000;\">{$GLOBALS['lang']['erecovery']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['recoverytips']}</a>")."
						</fieldset>
						<fieldset>
							<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['save']}\" />
						</fieldset>													
					</form>
					<div class=\"clearfix\">&nbsp;</div>
				</div>
			</div>
			<div id=\"signup\" class=\"floatingdialog\">
				<div class=\"form-small\">		
					<h3 class=\"center\">{$GLOBALS['lang']['signup']}</h3>
					<p style=\"text-align: center;\">{$GLOBALS['lang']['signup_intro']}</p>
					<form action=\"/signup_action\" method=\"post\" id=\"valid\" class=\"center\">
						<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
						<fieldset>
							<input class=\"auto\" type=\"text\" value=\"".($_SESSION['JOIN_CODE']?"{$_SESSION['JOIN_CODE']}":"{$GLOBALS['lang']['code']}")."\" name=\"code\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['code']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['code']}' : this.value; this.value=='{$GLOBALS['lang']['code']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\" />
							".(isset($_GET['ecode'])?"<span class=\"help-block\" style=\"color: #bc0000;\">{$GLOBALS['lang']['ecode']}</span>":"")."
						</fieldset>						
						<fieldset>
							<input class=\"auto\" type=\"text\" value=\"".($_SESSION['JOIN_EMAIL']?"{$_SESSION['JOIN_EMAIL']}":"{$GLOBALS['lang']['email']}")."\" name=\"email\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['email']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['email']}' : this.value; this.value=='{$GLOBALS['lang']['email']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\" />
						</fieldset>
						<fieldset>
							<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['signup']}\" ".($_SESSION['JOIN_STATUS']===0?'disabled':'')." />
						</fieldset>
					</form>
				</div>
			</div>
			<div id=\"register\" class=\"floatingdialog\">
				<div class=\"form-small\">		
					<h3 class=\"center\">{$GLOBALS['lang']['signup']}</h3>
					<p style=\"text-align: center;\">{$GLOBALS['lang']['signup_explain']}</p>
					<form action=\"/confirm_action\" method=\"post\" id=\"valid\" class=\"center\">
						<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
						<input type=\"hidden\" name=\"email\" value=\"{$_SESSION['REGISTER']['EMAIL']}\" />
						<input type=\"hidden\" name=\"id\" value=\"{$_SESSION['REGISTER']['ID']}\" />
						<input type=\"hidden\" name=\"origin\" value=\"{$_SESSION['REGISTER']['ORIGIN']}\" />
						<fieldset>
							<input class=\"auto\" type=\"text\" value=\"".($_SESSION['JOIN_USER']?"{$_SESSION['JOIN_USER']}":"{$GLOBALS['lang']['username']}")."\" name=\"username\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['username']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['username']}' : this.value; this.value=='{$GLOBALS['lang']['username']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\" />
							".(isset($_GET['eregister'])?"<span class=\"help-block\" style=\"color: #bc0000;\">{$GLOBALS['lang']['eregister']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['usertip']}</a>")."
						</fieldset>
						<fieldset>
							<input class=\"auto\" type=\"password\" value=\"{$GLOBALS['lang']['password']}\" name=\"password\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['password']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['password']}' : this.value; this.value=='{$GLOBALS['lang']['password']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\"/>							
						</fieldset>		
						<fieldset>	
							<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['signup']}\" ".($_SESSION['JOIN_STATUS']===0?'disabled':'')." />
						</fieldset>
					</form>
				</div>
			</div>
			<div id=\"changepass\" class=\"floatingdialog\">
				<div class=\"form-small\">		
					<h3 class=\"center\">{$GLOBALS['lang']['changepass']}</h3>
					<p style=\"text-align: center;\">{$GLOBALS['lang']['changepass_explain']}</p>
					<form action=\"/change_password_action\" method=\"post\" id=\"valid\" class=\"center\">
						<input type=\"hidden\" name=\"token\" value=\"{$_SESSION['CHANGEPASS']['TOKEN']}\" />
						<input type=\"hidden\" name=\"user\" value=\"{$_SESSION['CHANGEPASS']['USER']}\" />
						<fieldset>
							<input class=\"auto\" type=\"password\" value=\"{$GLOBALS['lang']['password']}\" name=\"password\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['password']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['password']}' : this.value; this.value=='{$GLOBALS['lang']['password']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\"/>							
							".(isset($_GET['echangepassword'])?"<span class=\"help-block\" style=\"color: #bc0000;\">{$GLOBALS['lang']['echangepassword']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['changetip']}</a>")."
						</fieldset>
						<fieldset>
							<input class=\"auto\" type=\"password\" value=\"{$GLOBALS['lang']['confirm']}\" name=\"confirm\" onfocus=\"this.value = this.value=='{$GLOBALS['lang']['confirm']}' ? '' : this.value; this.style.color='#4c4c4c';\" onfocusout=\"this.value = this.value == '' ? this.value = '{$GLOBALS['lang']['confirm']}' : this.value; this.value=='{$GLOBALS['lang']['confirm']}' ? this.style.color='#cccccc' : this.style.color='#4c4c4c'\"/>							
							<span class=\"help-block\">{$GLOBALS['lang']['confirmtip']}</a>
						</fieldset>					
						<fieldset>	
							<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['change']}\" />
						</fieldset>
					</form>
				</div>
			</div>
		";

		if( $_SESSION['CHANGEPASS']['TOKEN'] && $_SESSION['CHANGEPASS']['USER'] )
		{
			$objects .= "
						<script type=\"text/javascript\">
							$(document).ready(function() {
								$(\"#changepass\").dialog(\"open\");
								$(\".ui-dialog-titlebar\").hide();
							});
						</script>
			";
		}		
		if( $_SESSION['FORM']['OPEN'] )
		{
			$objects .= "<script type=\"text/javascript\">
							$(document).ready(function() {
								$(\"#{$_SESSION['FORM']['OPEN']}\").dialog(\"open\");
									$(\".ui-dialog-titlebar\").hide();
							});
						</script>";
			unset($_SESSION['FORM']['OPEN']);
		}
		
		if( $_SESSION['MESSAGE'] )
		{
			$objects .= "<div id=\"message\">
				<img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/notifications/{$_SESSION['MESSAGE']['TYPE']}.png\" /><br />
				<p>{$_SESSION['MESSAGE']['TEXT']}</p>
			</div>
			";
		 }

		if( isset($_GET['elogin']) )
		{
			$objects .= "<script type=\"text/javascript\">
							$(document).ready(function() {
								$(\"#login\").dialog(\"open\");
								$(\".ui-dialog-titlebar\").hide();
							});
							function recovery()
							{
								$(\"#login\").html($('#recovery').html());
							}
							
							function norecovery()
							{
								$(\"#login\").html($('#login-base').html());
							}
						</script>
			";
		}

		if( isset($_GET['erecovery']) )
		{
			$objects .= "<script type=\"text/javascript\">
								$(\"#login\").html($('#recovery').html());
						</script>";
		}
		if( isset($_GET['ecode']) )
		{
			$objects .= "<script type=\"text/javascript\">
							$(document).ready(function() {
								$(\"#signup\").dialog(\"open\");
								$(\".ui-dialog-titlebar\").hide();
							});
						</script>";
		}
		
		if( $_SESSION['REGISTER']['STATUS'] === true )
		{
			$objects .= "<script type=\"text/javascript\">
							$(document).ready(function() {
								$(\"#register\").dialog(\"open\");
								$(\".ui-dialog-titlebar\").hide();
							});
						</script>";	
						
			$_SESSION['REGISTER'] = false;
		}
		
		if( $_SESSION['MESSAGE'] )
		{
			$objects .= "<script type=\"text/javascript\">
							$(document).ready(function() {
								$(\"#message\").dialog(\"open\");
								$(\".ui-dialog-titlebar\").hide();
							});
						</script>";
			
			// we displayed it, clear it
			$_SESSION['MESSAGE'] = false;
		}
		
		return $objects;
	
	}
}

?>