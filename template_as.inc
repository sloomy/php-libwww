<?php

class template_as extends template
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
		$GLOBALS['lang']->import($GLOBALS['CONFIG']['CLASSPATH'] . '/template_as.lang');
		
		$top = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">
<html xmlns=\"http://www.w3.org/1999/xhtml\">
	<head>
		<title>{$GLOBALS['lang']['TITLE']}</title>
		<meta name=\"description\" content=\"{$GLOBALS['lang']['DESCRIPTION']}\" />
		<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />
		<meta name=\"viewport\" content=\"width=device-width; initial-scale=1.0; maximum-scale=1.0; user-scalable=0;\">
		<link rel=\"shortcut icon\" href=\"https://www.anotherservice.com/{$GLOBALS['CONFIG']['SITE']}/images/favicon.ico\" />
		<link href=\"/{$GLOBALS['CONFIG']['SITE']}/css/style.css\" rel=\"stylesheet\" type=\"text/css\" />
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/footer.js\"></script>
		<script type=\"text/javascript\">var APP_SITE = '{$GLOBALS['CONFIG']['SITE']}';</script>
		<link href=\"https://fonts.googleapis.com/css?family=Cuprum\" rel=\"stylesheet\" type=\"text/css\" />
	</head>
	<body>
		<div id=\"wrapper\">
			<div id=\"header\">
				<div class=\"container\">
					<div class=\"logo\">
						<a href=\"/\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/logo.png\" alt=\"Another Service\"></a>
					</div>
					<div class=\"menu\">
						<ul>
	";
			$top .= $this->getMainMenu();

			$top .= "
						</ul>
					</div>
				</div>
			</div>
";

		if( strstr($GLOBALS['CONFIG']['PAGE'], 'default') == false )
		{
			$top .= $this->getSubMenu();
			$top .= "<div id=\"box\">";
		}
		
		return $top;
	}
	
	private function getMainMenu()
	{
		$menu_file = $GLOBALS['CONFIG']['ROOT'].$GLOBALS['CONFIG']['SITE'].'/mainmenu.inc';
		if( file_exists($menu_file) )
		{
			$menu_data = include_once($menu_file);
			$menu = "";
			$logged = $GLOBALS['security']->hasAccess('/');
			foreach( $menu_data as $menu_item )
			{
				// check if the user has access to the target link
				$a = $GLOBALS['security']->hasAccess($menu_item['link']);
				if( ($menu_item['anonymous'] && !$logged) || (!$menu_item['anonymous'] && $a) )
				{
					$active = '';
					if( preg_match('#^'.rtrim($menu_item['link'], '/').'(/index)?$#', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
						$active = "class=\"active\"";
						
					$menu .= "
						<li id=\"{$menu_item['text']}\" {$active}>
							<a href=\"{$menu_item['link']}\" title=\"\">{$GLOBALS['lang'][$menu_item['text']]}</a>
						</li>
					";
				}
			}
			
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
			$current = 'n' . str_replace('/', '', $GLOBALS['CONFIG']['PAGE']);
			$menu_data = include_once($menu_file);
			$menu = "
				<!-- Left navigation -->
				<div id=\"submenu\">
					<div class=\"left\">
						{$GLOBALS['lang'][$current]}
					</div>
					<ul>
			";
			foreach( $menu_data as $menu_item )
			{
				// check if the user has access to the target link
				if( $GLOBALS['security']->hasAccess($menu_item['link']) )
				{
					$active = '';
					if( preg_match('#^'.rtrim($menu_item['link'], '/').'(/index)?$#', rtrim($GLOBALS['CONFIG']['PAGE'], '/')) )
						$active = "class=\"active\"";
					$class = $menu_item['text'];
					if( isset($menu_item['icon']) )
						$class = $menu_item['icon'];
					$menu .= "
						<li {$active}><a href=\"{$menu_item['link']}\" title=\"\"><span class=\"{$class}\">{$GLOBALS['lang'][$menu_item['text']]}</span></a></li>
					";
				}
			}
			
			$menu .= "
					</ul>
				</div>";
			
			return $menu;
		}
		else
			return "";
	}
	
	public function bottom()
	{
		$bottom = "";
		
		if( strstr($GLOBALS['CONFIG']['PAGE'], 'default') == false )
			$bottom .= "<div class=\"clearfix\"></div></div>";
		
		$bottom .= "
			<!-- Footer -->
			<div id=\"footer\">
				<div class=\"container\">
					<div class=\"column1\">
						<h1 class=\"footer\">{$GLOBALS['lang']['ABOUT']}</h1>
						<p>{$GLOBALS['lang']['ABOUT_TEXT']}</p>
					</div>
					<div class=\"column2\">
						<h1 class=\"footer\">{$GLOBALS['lang']['INFO']}</h1>
						<ul class=\"simple\">
							<li>{$GLOBALS['lang']['INFO_1']}</li>
							<li>{$GLOBALS['lang']['INFO_2']}</li>
							<li>{$GLOBALS['lang']['INFO_3']}</li>
							<li>{$GLOBALS['lang']['INFO_4']}</li>
						</ul>
					</div>
					<div class=\"column3\">
						<h1 class=\"footer\">{$GLOBALS['lang']['RESOURCES']}</h1>
						<ul class=\"simple\">
							<li>{$GLOBALS['lang']['RES_1']}</li>
							<li>{$GLOBALS['lang']['RES_2']}</li>
							<li>{$GLOBALS['lang']['RES_3']}</li>
							<li>{$GLOBALS['lang']['RES_4']}</li>
						</ul>
					</div>
					<div class=\"column4\">
						<h1 class=\"footer\">{$GLOBALS['lang']['SOCIAL']}</h1>
						<ul id=\"social\">
							<li id=\"facebook\"><a href=\"https://www.facebook.com/another.service\">Facebook</a></li>
							<li id=\"twitter\"><a href=\"https://twitter.com/anotherservice\">Twitter</a></li>
							<li id=\"linkedin\"><a href=\"http://www.linkedin.com/company/s-y-s-sas\">LinkedIn</a></li>
						</ul>
					</div>
					<div class=\"clearfix\"></div>
				</div>
			</div>
			<div id=\"copyright\">
				<div class=\"container\">
					{$GLOBALS['lang']['COPYRIGHT']}
				</div>
			</div>
		</div>
	</body>
</html>";
		
		return $bottom;
	}
}

?>