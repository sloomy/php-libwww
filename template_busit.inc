<?php

class template_busit extends template
{
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

		$content = "
			<div class=\"content\">
				<div class=\"nNote nFailure\"";
		
		if( $detail != null )
		{
			$content .= "onClick=\"document.getElementById('errorDebug').style.display = (document.getElementById('errorDebug').style.display=='none'?'block':'none');\"";
		}
		
		$content .= ">
					<p>".nl2br($message)."</p>";
		
		if( $detail != null )
		{
			$content .= "
					<div id=\"errorDebug\" style=\"display: none; margin-left: 55px; font-family: Courier New; margin-bottom: 20px;\">
						<strong>".nl2br($detail)."</strong>";
		}
		
		if( $stack != null )
		{
			$stack = preg_replace("/^#+[0-9\\-]* (.+)$/m", "<li>\$1</li>", $stack);
			$stack = preg_replace("/(\\{main\\}<\\/li>.)/s", "\$1</ol><ol style=\"border-left: 2px solid #E18B7C; margin-top: 10px; margin-bottom: 20px; padding-left: 20px; list-style: decimal inside;\">", $stack);
			$content .= "<ol style=\"border-left: 2px solid #E18B7C; margin-top: 10px; margin-bottom: 20px; padding-left: 20px; list-style: decimal inside;\">";
			$content .= $stack;
			$content .= "</ol>";
		}
		
		if( $detail != null )
		{
			$content .= "
					</div>";
		}
		
		$content .= "
				</div>
			</div>";
			
		$this->output($content);
	}
	
	public function top()
	{
		$GLOBALS['lang']->import($GLOBALS['CONFIG']['CLASSPATH'] . '/template_busit.lang');
		
		$top = "
<!DOCTYPE html>
<html>
	<head>
		<title>{$GLOBALS['lang']['TITLE']}</title>
		<meta name=\"description\" content=\"{$GLOBALS['lang']['DESCRIPTION']}\" />
		<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />
		<meta http-equiv=\"Cache-control\" content=\"no-cache\">
		<meta http-equiv=\"Expires\" CONTENT=\"-1\">
		<link rel=\"shortcut icon\" href=\"https://www.bus-it.com/{$GLOBALS['CONFIG']['SITE']}/img/favicon.ico\" />
		<link href=\"https://fonts.googleapis.com/css?family=Cuprum\" rel=\"stylesheet\" type=\"text/css\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/main.css\" type=\"text/css\" />
		<link rel=\"stylesheet\" href=\"/{$GLOBALS['CONFIG']['SITE']}/css/helper.css\" type=\"text/css\" />
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/helper.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/footer.js\"></script>
		<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>
		</head>
	<body>
	<div id=\"wrapper\">
		<div id=\"header\">
			<div class=\"head\">
				<div class=\"logo\">
					<a href=\"/home\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/logo.png\" alt=\"logo\" /></a>
				</div>
				<div class=\"menu\">";

if( !$GLOBALS['CONFIG']['INSTANCE'] )	
		$top .= $this->getMainMenu();
			
		$top .= "
				</div>
			</div>
		</div>
";

if( $_SESSION['MESSAGE'] )
{
	$top .= "
		<div id=\"message\">
			<img class=\"icon\" src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/notifications/".($_SESSION['MESSAGE']['TYPE']=='success'?"accept":"error").".png\" />
			{$_SESSION['MESSAGE']['TEXT']}
			<br />
			<div style=\"text-align: right\"><a href=\"#\" onclick=\"document.getElementById('message').style.visibility = 'hidden';\">{$GLOBALS['lang']['DISMISS']}</a></div>
		</div>
	";
	
	// we displayed it, clear it
	$_SESSION['MESSAGE'] = false;
}

$top .= "
		<div id=\"container\">";
	
		$logged = $GLOBALS['security']->hasAccess('/panel');

		if( strstr($GLOBALS['CONFIG']['PAGE'], 'panel') !== false || strstr($GLOBALS['CONFIG']['PAGE'], 'help') !== false  )
		{
			$top .= "
			<div class=\"box\">";
			$top .= $this->getSubMenu();
		}
				
		return $top;
	}
	
	private function getMainMenu()
	{
		$menu_file = $GLOBALS['CONFIG']['ROOT'].$GLOBALS['CONFIG']['SITE'].'/mainmenu.inc';
		if( file_exists($menu_file) )
		{
			$menu_data = include_once($menu_file);
			$menu = "
					<ul>";

			$logged = $GLOBALS['security']->hasAccess('/panel');
			foreach( $menu_data as $menu_item )
			{
				// check if the user has access to the target link
				$a = $GLOBALS['security']->hasAccess($menu_item['link']);
				if( ($menu_item['anonymous'] && !$logged) || (!$menu_item['anonymous'] && $a) )
				{
					$active = '';
					if( preg_match('#^'.rtrim($menu_item['link'], '/').'(/index)?$#', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
						$active = "class=\"active\"";
					
					if( !$logged && !$menu_item['anonymous'] )
						continue;
					else
					{
					$menu .= "
						<li><a href=\"{$menu_item['link']}\" title=\"\" {$active}>{$GLOBALS['lang'][$menu_item['text']]}</a></li>";
					}
				}
			}
			
			$menu .= "
					</ul>
			";
			
			return $menu;
		}
		else
			return "";
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
					<div class=\"nav\">
						<ul class=\"tabs\">
			";
			
			// check which submenu is active
			$active = null;
			foreach( $menu_data as $menu_item )
			{
				// check if the user has access to the target link
				if( $GLOBALS['security']->hasAccess($menu_item['link']) )
				{
					if( preg_match('#^'.rtrim($menu_item['link'], '/').'(/index)?$#', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
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

					$menu .= "
							<li {$a}><a href=\"{$menu_item['link']}\" title=\"\">{$GLOBALS['lang'][$menu_item['text']]}</a></li>
					";
				}
			}
			
			$menu .= "
						</ul>
			";
			
			if( strstr($GLOBALS['CONFIG']['PAGE'], 'panel') !== false )
			{
				$menu .= "
						<div class=\"icon\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/large/user.png\" alt=\"logo\" /></div>
						<h5>".security::get('USER')."</h5>
				";
			}
			else if( strstr($GLOBALS['CONFIG']['PAGE'], 'help') !== false )
			{
				$menu .= "
						<div class=\"icon\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/large/help.png\" alt=\"logo\" /></div>
						<h5>{$GLOBALS['lang']['HELP']}</h5>
				";						
			}
			
			$menu .= "</div>";
			
			return $menu;
		}
		else
			return "";
	}
	
	public function bottom()
	{
		$bottom = "";
		$logged = $GLOBALS['security']->hasAccess('/panel');
		if( strstr($GLOBALS['CONFIG']['PAGE'], 'panel') !== false || strstr($GLOBALS['CONFIG']['PAGE'], 'help') !== false )
			$bottom .= "</div>";
		
		$bottom .= "	
		</div>
		<div id=\"footer\">
			<script>
				function redirect()
				{
					var obj = document.getElementById('language');
					var val = obj.options[obj.selectedIndex].value;
					document.location.href='?lang='+val;
				}
			</script>
			<div class=\"core\">
				<div class=\"copyright\">
					<div class=\"styled\">
						<select onchange=\"redirect(); this.style.background=this.options[this.selectedIndex].style.background\" id=\"language\" class=\"styled\" name=\"lang\">
							<option style=\"background-color: #4e7ba3;\" ".(translator::getLanguage()=='FR'?"selected":"")." value=\"fr\">Français</option>
							<option style=\"background-color: #4e7ba3;\" ".(translator::getLanguage()=='EN'?"selected":"")." value=\"en\">English</option>
						</select>
					</div>
					{$GLOBALS['lang']['COPYRIGHT']} - 
				</div>
				<div class=\"menu\">
";
if( !$GLOBALS['CONFIG']['INSTANCE'] )
{
	$bottom .= "<ul>
						<li><a href=\"/about\">{$GLOBALS['lang']['ABOUT']}</a></li>
						<li><a href=\"/about/contact\">{$GLOBALS['lang']['CONTACT']}</a></li>
						<li><a href=\"/help\">{$GLOBALS['lang']['HELP']}</a></li>
						<li><a href=\"http://developers.bus-it.com\">{$GLOBALS['lang']['DEVELOPERS']}</a></li>
						<li><a href=\"/about/legal\">{$GLOBALS['lang']['LEGAL']}</a></li>
						<li><a href=\"http://blog.bus-it.com\">{$GLOBALS['lang']['BLOG']}</a></li>
					</ul>
	";
}

$bottom .= "
				</div>
			</div>
		</div>
	</div>
<!-- Piwik --> 
<script type=\"text/javascript\">
var pkBaseURL = ((\"https:\" == document.location.protocol) ? \"https://stats.anotherservice.com/\" : \"http://stats.anotherservice.com/\");
document.write(unescape(\"%3Cscript src='\" + pkBaseURL + \"piwik.js' type='text/javascript'%3E%3C/script%3E\"));
</script><script type=\"text/javascript\">
try {
var piwikTracker = Piwik.getTracker(pkBaseURL + \"piwik.php\", 8);
piwikTracker.trackPageView();
piwikTracker.enableLinkTracking();
} catch( err ) {}
</script><noscript><p><img src=\"http://stats.anotherservice.com/piwik.php?idsite=8\" style=\"border:0\" alt=\"\" /></p></noscript>
<!-- End Piwik Tracking Code -->
	</body>
</html>";
		
		return $bottom;
	}
}

?>