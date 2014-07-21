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
		<meta http-equiv=\"cache-control\" content=\"no-cache, must-revalidate\" /> 
		<meta name=\"viewport\" content=\"width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no\" /> 
		<link rel=\"shortcut icon\" href=\"/{$GLOBALS['CONFIG']['SITE']}/images/favicon.ico\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/main.css\" type=\"text/css\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/font-awesome.css\" type=\"text/css\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/jquery-1.10.4/jquery-ui-1.10.4.custom.min.css\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/jquery-1.10.4/default.css\" />
		<link href=\"https://fonts.googleapis.com/css?family=Cuprum\" rel=\"stylesheet\" type=\"text/css\" />
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-2.1.1.min.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-globalize.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-ui-1.10.4.custom.min.js\"></script>
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
if( strstr($GLOBALS['CONFIG']['PAGE'], 'panel') !== false )
	$top .= "<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/panel.js\"></script>";
	
$top .= "
	</head>
	<body>
	<div id=\"wrapper\" style=\"";
	if( strstr($GLOBALS['CONFIG']['PAGE'], 'status') !== false )
		$top .= "background-color: #f0f0f0; ";
	else if( strstr($GLOBALS['CONFIG']['PAGE'], 'store') !== false && strstr($GLOBALS['CONFIG']['PAGE'], 'connector') === false )
		$top .= "background-color: #f0f0f0; ";
	else if( strstr($GLOBALS['CONFIG']['PAGE'], 'panel') !== false || strstr($GLOBALS['CONFIG']['PAGE'], 'admin') !== false )
		$top .= "background-color: #f0f0f0;";
	else if( strstr($GLOBALS['CONFIG']['PAGE'], 'case') !== false )
		$top .= "background-color: #f0f0f0;";
	else if( strstr($GLOBALS['CONFIG']['PAGE'], 'companies') !== false )
		$top .= "background-color: #f0f0f0;";
		
	$top .= "\">
		<div id=\"success\"></div>
		<div id=\"loading\"></div>
		<div id=\"overlay\"></div>";
	
if( strstr($GLOBALS['CONFIG']['PAGE'], 'default') != 42 )
{
	$top .= "
		<header>
			<div class=\"content\">
				<div class=\"logo\">
					<a href=\"/\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/logo.png\" alt=\"logo\" /></a>
				</div>
	";
	
	if( !$GLOBALS['CONFIG']['INSTANCE'] )	
		$top .= $this->getMainMenu();
			
	$top .= "
			</div>
		</header>
	";
}

$top .= "
		<div class=\"core\" id=\"core\" style=\""; 
if( strstr($GLOBALS['CONFIG']['PAGE'], 'status') !== false )
	$top .= "background-color: #f0f0f0; ";
else if( strstr($GLOBALS['CONFIG']['PAGE'], 'panel') !== false || strstr($GLOBALS['CONFIG']['PAGE'], 'admin') !== false )
	$top .= "background-color: #f0f0f0;";
else if( strstr($GLOBALS['CONFIG']['PAGE'], 'store') !== false && strstr($GLOBALS['CONFIG']['PAGE'], 'connector') === false )
	$top .= "background-color: #f0f0f0;";
else if( strstr($GLOBALS['CONFIG']['PAGE'], 'case') !== false )
	$top .= "background-color: #f0f0f0;";
else if( strstr($GLOBALS['CONFIG']['PAGE'], 'companies') !== false )
	$top .= "background-color: #f0f0f0;";
		
$top .= "\">";
	
		$logged = $GLOBALS['security']->hasAccess('/panel');
		$top .= $this->getSubMenu();
		
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
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/font-awesome.css\" type=\"text/css\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/jquery-1.10.4/jquery-ui-1.10.4.custom.min.css\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/jquery-1.10.4/default.css\" />
		<link href=\"https://fonts.googleapis.com/css?family=Cuprum\" rel=\"stylesheet\" type=\"text/css\" />
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-2.1.1.min.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-globalize.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/jquery/jquery-ui-1.10.4.custom.min.js\"></script>
	</head>
	<body style=\"padding-top: 20px;\">
		";
		
		return $top;
	}
	
	private function getMainMenu()
	{
		if( strstr($GLOBALS['CONFIG']['PAGE'], 'default') != 42 )
		{
			$menu_file = $GLOBALS['CONFIG']['ROOT'].$GLOBALS['CONFIG']['SITE'].'/mainmenu.inc';
			if( file_exists($menu_file) )
			{
				$menu_data = include_once($menu_file);
				$menu = "
				<span class=\"nav-mobile\" id=\"nav-mobile\"><a href=\"#\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/nav.png\" /></a></span>
				<nav id=\"navigation\">
					<ul id=\"mainmenu\">";

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
										".($menu_item['icon']?"<i class=\"fa fa-{$menu_item['icon']}-o fa-fw\"></i>":"")." <a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\" title=\"\" {$active}>{$GLOBALS['lang'][$menu_item['text']]}</a>
										<ul>";
									foreach( $menu_item['sub'] as $menu_subitem )
									{
										if( strpos(rtrim($GLOBALS['CONFIG']['PAGE'], '/'), rtrim($menu_subitem['link'], '/')) === 0 )
										//if( preg_match('!^'.rtrim($menu_subitem['link'], '/').'(/index)?$!', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
											$subactive = "class=\"active\"";
						
										$menu .= "
												<li class=\"{$menu_subitem['text']}\">".($menu_subitem['icon']?"<i class=\"fa fa-{$menu_subitem['icon']}-o fa-fw\"></i>":"")." <a id=\"link-{$menu_subitem['text']}\" href=\"{$menu_subitem['link']}\" onclick=\"{$menu_subitem['onclick']}\" title=\"\" {$subactive}>{$GLOBALS['lang'][$menu_subitem['text']]}</a></li>";
									}
									
									$menu .= "
										</ul>
									</li>";
							}
							else
							{
								$menu .= "
						<li class=\"{$menu_item['text']}\">".($menu_item['icon']?"<i class=\"fa fa-{$menu_item['icon']}-o fa-fw\"></i>":"")." <a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\" title=\"\" {$active}>{$GLOBALS['lang'][$menu_item['text']]}</a></li>";
							}
						}
					}
				}
				
				$menu .= "
					</ul>
					<ul id=\"mainmenu-mob\" style=\"display: none;\">";

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
										".($menu_item['icon']?"<i class=\"fa fa-{$menu_item['icon']}-o fa-fw\"></i>":"")." <a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\" title=\"\" {$active}>{$GLOBALS['lang'][$menu_item['text']]}</a>
										<ul>";
									foreach( $menu_item['sub'] as $menu_subitem )
									{
										if( strpos(rtrim($GLOBALS['CONFIG']['PAGE'], '/'), rtrim($menu_subitem['link'], '/')) === 0 )
										//if( preg_match('!^'.rtrim($menu_subitem['link'], '/').'(/index)?$!', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
											$subactive = "class=\"active\"";
						
										$menu .= "
												<li class=\"{$menu_subitem['text']}\">".($menu_subitem['icon']?"<i class=\"fa fa-{$menu_subitem['icon']}-o fa-fw\"></i>":"")." <a id=\"link-{$menu_subitem['text']}\" href=\"{$menu_subitem['link']}\" onclick=\"{$menu_subitem['onclick']}\" title=\"\" {$subactive}>{$GLOBALS['lang'][$menu_subitem['text']]}</a></li>";
									}
									
									$menu .= "
										</ul>
									</li>";
							}
							else
							{
								$menu .= "
						<li class=\"{$menu_item['text']}\">".($menu_item['icon']?"<i class=\"fa fa-{$menu_item['icon']}-o fa-fw\"></i>":"")." <a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\" title=\"\" {$active}>{$GLOBALS['lang'][$menu_item['text']]}</a></li>";
							}
						}
					}
				}
				
				$menu .= "
					</ul>
				</nav>
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
					<div class=\"menu-fixed-mob\" id=\"menu-fixed-mob\">
						<a style=\"float: left;\" href=\"#\" id=\"submenu-mobile\">{$GLOBALS['lang']['MENUMOB']}</a>
						<ul style=\"display: none;\" id=\"submenu-nav-mob\">";
		
			foreach( $menu_data as $menu_item )
			{
				if( $GLOBALS['security']->hasAccess($menu_item['link']) )
				{
					if( is_array($menu_item['sub']) )
					{
						$menu .= "<li class=\"sub ".($menu_item['id']?"{$menu_item['id']}":"{$menu_item['text']}")."\">".($menu_item['icon']?"<a href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\" title=\"\" {$active}><i class=\"fa fa-{$menu_item['icon']}-o fa-fw\"></i>&nbsp;&nbsp;":"")." ".($GLOBALS['lang'][$menu_item['text']]?"{$GLOBALS['lang'][$menu_item['text']]}":"{$menu_item['text']}")."</a>
							<ul>";
								
						foreach( $menu_item['sub'] as $menu_subitem )
						{						
							$menu .= "
								<li class=\"{$menu_subitem['text']}\"><a href=\"{$menu_subitem['link']}\"  onclick=\"{$menu_subitem['onclick']}\" title=\"\">".($menu_subitem['icon']?"<i class=\"fa fa-{$menu_subitem['icon']} fa-fw\"></i>&nbsp;&nbsp;":"")." ".($GLOBALS['lang'][$menu_subitem['text']]?"{$GLOBALS['lang'][$menu_subitem['text']]}":"{$menu_subitem['text']}")."</a></li>";
						}
									
						$menu .= "
							</ul>
						</li>";
					}
					else
					{
						$menu .= "
						<li class=\"{$menu_item['text']}\"><a href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\">".($menu_item['icon']?"<i class=\"fa fa-{$menu_item['icon']} fa-fw\"></i>&nbsp;&nbsp;":"")." ".($GLOBALS['lang'][$menu_item['text']]?"{$GLOBALS['lang'][$menu_item['text']]}":"{$menu_item['text']}")."</a></li>
					";
					}
				}
			}
			
			$menu .= "
						</ul>	
			";

			if( strstr($GLOBALS['CONFIG']['PAGE'], 'store') !== false )
			{
				$names = api::send('busit/connector/selectindex', array('lang'=>translator::getLanguage()), $GLOBALS['CONFIG']['API_USERNAME'].':'.$GLOBALS['CONFIG']['API_PASSWORD']);
				$menu .= "
						<script>
							availableConnectors = [
							";
				foreach( $names as $n )
				{
					$menu .= "
							{
								value: \"{$n['connector_name']}\",
								id: \"{$n['connector_id']}\",
							},
					";
				}
				
				$menu .= "
							];
						</script>
						<form style=\"float: right; margin-right: 10px;\" id=\"searchform-mob\"><input type=\"hidden\" name=\"connectorid-mob\" value=\"\" id=\"connectorid-mob\" /><input type=\"submit\" style=\"display: none;\" /><input style=\"width: 200px;\" type=\"text\" id=\"search-mob\" placeholder=\"{$GLOBALS['lang']['search']}\" /></form>";
			}
			if( strstr($GLOBALS['CONFIG']['PAGE'], 'doc') !== false )
			{
				$menu .= "
						<form style=\"float: right; margin-right: 10px;\" id=\"searchform-mob\" action=\"/doc/".(strstr($GLOBALS['CONFIG']['PAGE'], 'developers')!==false?"developers/":"")."search\" method=\"get\"><input type=\"submit\" style=\"display: none;\" /><input name=\"search\" style=\"width: 200px;\" type=\"text\" id=\"search-mob\" placeholder=\"{$GLOBALS['lang']['search']}\" /></form>";
			}

			if( strstr($GLOBALS['CONFIG']['PAGE'], 'panel') !== false )
			{
				$self = api::send('self/system/user/select');
				$self = $self[0];			
				
				$menu .= "
					<div style=\"position: relative; float: right;\">
						<a href=\"#\" id=\"profile-mob\">
							<span style=\"display: block; float: left; padding: 13px 0 0 0;\">{$self['user_name']}</span>
							<img style=\"display: block; float: left; padding: 13px 0 0 10px;\" src=\"/{$GLOBALS['CONFIG']['SITE']}/images/arrow.png\" />
							<img class=\"profile-image\" src=\"".(file_exists("{$GLOBALS['CONFIG']['SITE']}/images/users/{$self['user_id']}.png")?"/{$GLOBALS['CONFIG']['SITE']}/images/users/{$self['user_id']}.png":"/{$GLOBALS['CONFIG']['SITE']}/images/users/user.png")."\" alt=\"\" />
						</a>
						<div id=\"profile-menu-mob\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/loading_dark_small.gif\" alt=\"\" class=\"loader\" style=\"margin-top: -20px;\" /></div>
					</div>
					";
			}
			
			$menu .= "
					</div>
					<div class=\"menu-fixed\" id=\"menu-fixed\">
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
						$menu .= "<li id=\"".($menu_item['id']?"{$menu_item['id']}":"{$menu_item['text']}")."\" class=\"sub ".($menu_item['id']?"{$menu_item['id']}":"{$menu_item['text']}")."\">".($menu_item['icon']?"<i class=\"fa fa-{$menu_item['icon']}-o fa-fw\"></i>&nbsp;&nbsp;":"")." <a id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\" title=\"\" {$active}>".($GLOBALS['lang'][$menu_item['text']]?"{$GLOBALS['lang'][$menu_item['text']]}":"{$menu_item['text']}")."</a>
							<ul>";
								
						foreach( $menu_item['sub'] as $menu_subitem )
						{
							if( strpos(rtrim($GLOBALS['CONFIG']['PAGE'], '/'), rtrim($menu_subitem['link'], '/')) === 0 )
							//if( preg_match('!^'.rtrim($menu_subitem['link'], '/').'(/index)?$!', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
								$subactive = "class=\"active\"";
						
							$menu .= "
								<li class=\"{$menu_subitem['text']}\"><a id=\"link-{$menu_subitem['text']}\" href=\"{$menu_subitem['link']}\"  onclick=\"{$menu_subitem['onclick']}\" title=\"\" {$subactive}>".($menu_subitem['icon']?"<i class=\"fa fa-{$menu_subitem['icon']}-o fa-fw\"></i>":"")." ".($GLOBALS['lang'][$menu_subitem['text']]?"{$GLOBALS['lang'][$menu_subitem['text']]}":"{$menu_subitem['text']}")."</a></li>";
						}
									
						$menu .= "
							</ul>
						</li>";
					}
					else
					{
						$menu .= "
									<li id=\"".($menu_item['id']?"{$menu_item['id']}":"{$menu_item['text']}")."\" class=\"{$menu_item['text']}\"><a {$a} id=\"link-{$menu_item['text']}\" href=\"{$menu_item['link']}\" onclick=\"{$menu_item['onclick']}\">".($menu_item['icon']?"<i class=\"fa fa-{$menu_item['icon']} fa-fw\"></i>&nbsp;&nbsp;":"")." ".($GLOBALS['lang'][$menu_item['text']]?"{$GLOBALS['lang'][$menu_item['text']]}":"{$menu_item['text']}")."</a></li>
						";
					}
				}
			}
			
			if( strstr($GLOBALS['CONFIG']['PAGE'], 'store') !== false )
			{
				$menu .= "
									<li id=\"search-li\" class=\"search\"><form id=\"searchform\"><input type=\"hidden\" name=\"connectorid\" value=\"\" id=\"connectorid\" /><input type=\"submit\" style=\"display: none;\" /><input style=\"width: 200px;\" type=\"text\" id=\"search\" placeholder=\"{$GLOBALS['lang']['search']}\" /></form></li>";
			}
			if( strstr($GLOBALS['CONFIG']['PAGE'], 'doc') !== false )
			{
				$menu .= "
									<li id=\"search-li\" class=\"search\"><form id=\"searchform\" action=\"/doc/".(strstr($GLOBALS['CONFIG']['PAGE'], 'developers')!==false?"developers/":"")."search\" method=\"get\"><input type=\"submit\" style=\"display: none;\" /><input name=\"search\"  style=\"width: 200px;\" type=\"text\" id=\"search\" placeholder=\"{$GLOBALS['lang']['search']}\" /></form></li>";
			}
			
			if( strstr($GLOBALS['CONFIG']['PAGE'], 'panel') !== false )
			{
				$menu .= "
					<div style=\"position: relative; float: right;\">
						<a href=\"#\" id=\"profile\">
							<span style=\"display: block; float: left; padding: 13px 0 0 0;\">{$self['user_name']}</span>
							<img style=\"display: block; float: left; padding: 13px 0 0 10px;\" src=\"/{$GLOBALS['CONFIG']['SITE']}/images/arrow.png\" />
							<img class=\"profile-image\" src=\"".(file_exists("{$GLOBALS['CONFIG']['SITE']}/images/users/{$self['user_id']}.png")?"/{$GLOBALS['CONFIG']['SITE']}/images/users/{$self['user_id']}.png":"/{$GLOBALS['CONFIG']['SITE']}/images/users/user.png")."\" alt=\"\" />
						</a>
						<div id=\"profile-menu\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/loading_dark_small.gif\" alt=\"\" class=\"loader\" style=\"margin-top: -20px;\" /></div>
					</div>
					";
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
		<div id=\"footer\" class=\"footer\" style=\"";
if( strstr($GLOBALS['CONFIG']['PAGE'], 'status') !== false )
	$bottom .= "background-color: #ffffff; ";
else if( strstr($GLOBALS['CONFIG']['PAGE'], 'store') !== false && strstr($GLOBALS['CONFIG']['PAGE'], 'connector') === false )
	$bottom .= "background-color: #ffffff;";	
else if( strstr($GLOBALS['CONFIG']['PAGE'], 'panel') !== false || strstr($GLOBALS['CONFIG']['PAGE'], 'admin') !== false )
	$bottom .= "background-color: #ffffff;";
else if( strstr($GLOBALS['CONFIG']['PAGE'], 'case') !== false )
	$bottom .= "background-color: #ffffff;";
else if( strstr($GLOBALS['CONFIG']['PAGE'], 'companies') !== false )
	$bottom .= "background-color: #ffffff;";
	
$bottom .= "\">
			<div class=\"content\">
				<div class=\"social\">
					<a class=\"link\" href=\"https://twitter.com/Bus_IT\">
						<img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/social/twitter.png\" alt=\"Twitter\" />
					</a>
					<a class=\"link\" href=\"https://www.facebook.com/busit.net\">
						<img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/social/facebook.png\" alt=\"Facebook\" />
					</a>
					<a class=\"link\" href=\"https://google.com/+BusitFr\">
						<img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/social/google.png\" alt=\"Google+\" />
					</a>
					<a class=\"link\" href=\"https://www.linkedin.com/company/5121205\">
						<img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/social/linkedin.png\" alt=\"LinkedIn\" />
					</a>
					<a class=\"link\" href=\"http://www.youtube.com/channel/UCvB9PQcyRzdf8n4AewdE_oA\">
						<img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/social/youtube.png\" alt=\"YouTube\" />
					</a>
					<div class=\"clear\"></div>
				</div>
				<br />
				<ul>
					<li><a href=\"/about\">{$GLOBALS['lang']['ABOUT']}</a></li>
					<li><a href=\"/about/press\">{$GLOBALS['lang']['PRESS']}</a></li>
					<li><a href=\"/about/contact\">{$GLOBALS['lang']['CONTACT']}</a></li>
					<li><a href=\"/about/team\">{$GLOBALS['lang']['TEAM']}</a></li>
					<li><a href=\"/doc\">{$GLOBALS['lang']['HELP']}</a></li>
					<li><a href=\"/developers\">{$GLOBALS['lang']['DEVELOPERS']}</a></li>
					<li><a href=\"/about/legal\">{$GLOBALS['lang']['LEGAL']}</a></li>
					<li><a href=\"/status\">{$GLOBALS['lang']['STATUS']}</a></li>
				</ul>
				<p style=\"margin: 10px 0 0 0; padding: 0; font-size: 12px;\">
	";
	$request = str_replace(array('?lang='.translator::getLanguage(), '&lang='.translator::getLanguage()) , array('', ''), $_SERVER['REQUEST_URI']);

	$bottom .= "
					".(translator::getLanguage()=='EN'?"<span style=\"color: #4d4d4d;\">":"<a href=\"{$request}".(strstr($request,'?')===false?"?":"&")."lang=EN\">")."English".(translator::getLanguage()=='EN'?"</span>":"</a>")."&nbsp;&nbsp;&nbsp;
					".(translator::getLanguage()=='FR'?"<span style=\"color: #4d4d4d;\">":"<a href=\"{$request}".(strstr($request,'?')===false?"?":"&")."lang=FR\">")."Fran&ccedil;ais".(translator::getLanguage()=='FR'?"</span>":"</a>")."&nbsp;&nbsp;&nbsp;
					".(translator::getLanguage()=='ES'?"<span style=\"color: #4d4d4d;\">":"<a href=\"{$request}".(strstr($request,'?')===false?"?":"&")."lang=ES\">")."Espa&ntilde;ol".(translator::getLanguage()=='ES'?"</span>":"</a>")."&nbsp;&nbsp;&nbsp;
				</p>
				<p>{$GLOBALS['lang']['COPYRIGHT']} | {$GLOBALS['lang']['SYS']}</p>
			</div>
		</div>
	</div>
	<div id=\"debug\" class=\"debug-fixed\" onclick=\"$('#bug').dialog('open'); return false;\">
		<div class=\"container\">
			{$GLOBALS['lang']['DEBUG']}
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
	</body>
</html>";
		
		return $bottom;
	}
	
	private function getObjects()
	{
		if( !isset($_SESSION['ANTISPAM']) )
			$_SESSION['ANTISPAM'] = md5(time().'busit');

		$objects = "
			<div id=\"login\" class=\"floatingdialog\" autocomplete=\"off\">
				<h3 class=\"center\">{$GLOBALS['lang']['login']}</h3>
				<form action=\"/login_action\" method=\"post\" class=\"center\">
					<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
					<fieldset>
						<input type=\"text\" placeholder=\"{$GLOBALS['lang']['username']}\" name=\"username\" />
					</fieldset>
					<fieldset>
						<input type=\"password\" placeholder=\"{$GLOBALS['lang']['password']}\" name=\"password\" />
						".(isset($_SESSION['ERROR']['MESSAGE']) && $_SESSION['ERROR']['HANDLER'] == 'login'?"<span class=\"help-block\" style=\"color: #bc0000;\">{$_SESSION['ERROR']['MESSAGE']}</span>":"")."
					</fieldset>						
					<fieldset>
						<input type=\"checkbox\" name=\"chbox\" />
						<label for=\"remember\" style=\"display: inline-block; padding-left: 10px;\">{$GLOBALS['lang']['remember']}</label>
					</fieldset>
					<fieldset>
						<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['login']}\" />
					</fieldset>							
				</form>
			</div>
			<div id=\"login-base\" class=\"floatingdialog\" autocomplete=\"off\">
				<h3 class=\"center\">{$GLOBALS['lang']['login']}</h3>
				<form action=\"/login_action\" method=\"post\" class=\"center\">
					<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
					<fieldset>
						<input type=\"text\" placeholder=\"{$GLOBALS['lang']['username']}\" name=\"username\" />
					</fieldset>
					<fieldset>
						<input type=\"password\" placeholder=\"{$GLOBALS['lang']['password']}\" name=\"password\" />
						".(isset($_SESSION['ERROR']['MESSAGE']) && $_SESSION['ERROR']['HANDLER'] == 'login'?"<span class=\"help-block\" style=\"color: #bc0000;\">{$_SESSION['ERROR']['MESSAGE']}</span>":"")."
					</fieldset>
					<fieldset>
						<input type=\"checkbox\" name=\"chbox\" />
						<label for=\"remember\" style=\"display: inline-block; padding-left: 10px;\">{$GLOBALS['lang']['remember']}</label>
					</fieldset>
					<fieldset>
						<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['login']}\" />
					</fieldset>													
				</form>
			</div>
			<div id=\"recovery\" class=\"floatingdialog\" autocomplete=\"off\">
				<h3 class=\"center\">{$GLOBALS['lang']['recovery']}</h3>
				<form action=\"/recovery_action\" method=\"post\" class=\"center\">
					<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
					<fieldset>
						<input type=\"text\" placeholder=\"{$GLOBALS['lang']['username']}\" name=\"username\" />
						".(isset($_SESSION['ERROR']['MESSAGE']) && $_SESSION['ERROR']['HANDLER'] == 'recovery'?"<span class=\"help-block\" style=\"color: #bc0000;\">{$_SESSION['ERROR']['MESSAGE']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['recoverytips']}</span>")."
					</fieldset>
					<fieldset>
						<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['save']}\" />
					</fieldset>													
				</form>
			</div>
			<div id=\"signup\" class=\"floatingdialog\" autocomplete=\"off\">	
				<h3 class=\"center\">{$GLOBALS['lang']['signup']}</h3>
				<form action=\"/signup_action\" method=\"post\" id=\"valid\" class=\"center\">
					<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />				
					<fieldset>
						<input type=\"text\" placeholder=\"{$GLOBALS['lang']['email']}\" name=\"email\" />
						".(isset($_SESSION['ERROR']['MESSAGE']) && $_SESSION['ERROR']['HANDLER'] == 'signup'?"<span class=\"help-block\" style=\"color: #bc0000;\">{$_SESSION['ERROR']['MESSAGE']}</span>":"")."
					</fieldset>
					<fieldset>
						<input type=\"checkbox\" name=\"conditions\" value=\"1\" />
						{$GLOBALS['lang']['conditions']}
					</fieldset>
					<fieldset>
						<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['signup']}\" ".($_SESSION['JOIN_STATUS']===0?'disabled':'')." />
					</fieldset>
				</form>
			</div>
			<div id=\"register\" class=\"floatingdialog\" autocomplete=\"off\">
				<h3 class=\"center\">{$GLOBALS['lang']['signup']}</h3>
				<p style=\"text-align: center;\">{$GLOBALS['lang']['signup_explain']}</p>
				<form action=\"/confirm_action\" method=\"post\" id=\"valid\" class=\"center\">
					<input type=\"hidden\" name=\"antispam\" value=\"{$_SESSION['ANTISPAM']}\" />
					<input type=\"hidden\" name=\"email\" value=\"{$_SESSION['REGISTER']['EMAIL']}\" />
					<input type=\"hidden\" name=\"id\" value=\"{$_SESSION['REGISTER']['ID']}\" />
					<input type=\"hidden\" name=\"origin\" value=\"{$_SESSION['REGISTER']['ORIGIN']}\" />
					<fieldset>
						<input style=\"width: 240px;\" type=\"text\" placeholder=\"{$GLOBALS['lang']['username']}\" name=\"username\" />
						".(isset($_SESSION['ERROR']['MESSAGE']) && $_SESSION['ERROR']['HANDLER'] == 'register'?"<span class=\"help-block\" style=\"color: #bc0000;\">{$_SESSION['ERROR']['MESSAGE']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['usertip']}</span>")."
					</fieldset>
					<fieldset>
						<input style=\"width: 240px;\" type=\"password\" placeholder=\"{$GLOBALS['lang']['password']}\" name=\"password\" />
					</fieldset>
					<fieldset>	
						<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['signup']}\" ".($_SESSION['JOIN_STATUS']===0?'disabled':'')." />
					</fieldset>
				</form>
			</div>
			<div id=\"changepass\" class=\"floatingdialog\">
				<h3 class=\"center\">{$GLOBALS['lang']['changepass']}</h3>
				<p style=\"text-align: center;\">{$GLOBALS['lang']['changepass_explain']}</p>
				<form action=\"/change_password_action\" method=\"post\" id=\"valid\" class=\"center\">
					<input type=\"hidden\" name=\"token\" value=\"{$_SESSION['CHANGEPASS']['TOKEN']}\" />
					<input type=\"hidden\" name=\"user\" value=\"{$_SESSION['CHANGEPASS']['USER']}\" />
					<fieldset>
						<input type=\"password\" placeholder=\"{$GLOBALS['lang']['password']}\" name=\"password\"  />							
						".(isset($_GET['echangepassword'])?"<span class=\"help-block\" style=\"color: #bc0000;\">{$GLOBALS['lang']['echangepassword']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['changetip']}</span>")."
					</fieldset>
					<fieldset>
						<input type=\"password\" placeholder=\"{$GLOBALS['lang']['confirm']}\" name=\"confirm\" />							
						<span class=\"help-block\">{$GLOBALS['lang']['confirmtip']}</a>
					</fieldset>					
					<fieldset>	
						<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['change']}\" />
					</fieldset>
				</form>
			</div>
			<div id=\"bug\" class=\"floatingdialog\">
				<br />
				<h3 class=\"center\">{$GLOBALS['lang']['newbug']}</h3>
				<form action=\"/bugreport_action\" method=\"post\" class=\"center\">
					<fieldset>
						<input type=\"text\" class=\"large\" placeholder=\"{$GLOBALS['lang']['newbug_name']}\" name=\"email\" />
						".(isset($_SESSION['ERROR']['MESSAGE']) && $_SESSION['ERROR']['HANDLER'] == 'bugreport'?"<span class=\"help-block\" style=\"color: #bc0000;\">{$_SESSION['ERROR']['MESSAGE']}</span>":"<span class=\"help-block\">{$GLOBALS['lang']['newbug_name_help']}</span>")."
					</fieldset>
					<fieldset>
						<input type=\"text\" class=\"large\" placeholder=\"{$GLOBALS['lang']['newbug_desc']}\" name=\"desc\" />
						<span class=\"help-block\">{$GLOBALS['lang']['newbug_desc_help']}</span>
					</fieldset>
					<fieldset>
						<textarea class=\"large\" style=\"height: 150px;\" name=\"content\" placeholder=\"{$GLOBALS['lang']['newbug_content']}\"></textarea>
						<span class=\"help-block\">{$GLOBALS['lang']['newbug_content_help']}</span>
					</fieldset>
					<fieldset>	
						<input autofocus type=\"submit\" value=\"{$GLOBALS['lang']['newbug_submit']}\" />
					</fieldset>
				</form>							
			</div>
			<div id=\"message\" class=\"floatingdialog\">
				<img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/notifications/{$_SESSION['MESSAGE']['TYPE']}.png\" /><br />
				<p>{$_SESSION['MESSAGE']['TEXT']}</p>
			</div>
			
			<script type=\"text/javascript\">
				$(document).ready(function()
				{
		";
		if( strstr($GLOBALS['CONFIG']['PAGE'], 'store') !== false )
		{
			$objects .= "
					$(\"#search\").autocomplete({
							focus: function( event, ui ) {
								$('#search').val( ui.item.value );
							},
							select: function( event, ui ) {
								if( ui.item )
								{
									$('#connectorid').val(ui.item.id);
								}
								$(\"#searchform\").submit();
							},
							source: availableConnectors
						});
			";
		}
		
		if( $_SESSION['ERROR']['HANDLER'] == 'signup' )
			$objects .= " $(\"#signup\").dialog(\"open\");\n";
		if( $_SESSION['ERROR']['HANDLER'] == 'register' )	
			$objects .= " $(\"#register\").dialog(\"open\");\n";
		if( $_SESSION['REGISTER']['STATUS'] === true )
			$objects .= " $(\"#register\").dialog(\"open\");\n";
		if( $_SESSION['ERROR']['HANDLER'] == 'login' )	
			$objects .= " $(\"#login\").dialog(\"open\");\n";
		if( $_SESSION['ERROR']['HANDLER'] == 'bugreport' )	
			$objects .= " $(\"#bug\").dialog(\"open\");\n";
		if( $_SESSION['ERROR']['HANDLER'] == 'recovery' )	
			$objects .= "$(\"#login\").html($('#recovery').html()); $(\"#login\").dialog(\"open\");\n";
		if( $_SESSION['CHANGEPASS']['TOKEN'] && $_SESSION['CHANGEPASS']['USER'] )
			$objects .= "$(\"#changepass\").dialog(\"open\");\n";	
		if( $_SESSION['FORM']['OPEN'] )
			$objects .= "$(\"#{$_SESSION['FORM']['OPEN']}\").dialog(\"open\");\n";
		if( $_SESSION['MESSAGE'] )
			$objects .= "$(\"#message\").dialog(\"open\"); setTimeout(\"$('#message').dialog('close')\", 3000);\n";
		
		$objects .= "	
				});
			</script>
		";

		unset($_SESSION['ERROR']);
		unset($_SESSION['MESSAGE']);
		unset($_SESSION['FORM']['OPEN']);
		unset($_SESSION['REGISTER']['STATUS']);
		
		return $objects;
	
	}
}

?>