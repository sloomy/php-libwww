<?php

class template_on extends template
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
	
	public function notfound()
	{
		$content = "<div class=\"wrapper\">
			<div class=\"errorPage\">
				<h2 class=\"red errorTitle\"><span>What the hell are you doing !?</span></h2>
				<h1>404</h1>
				<span class=\"bubbles\"></span>
				<p>Yeah of course this page does not exist... What did you expect ?</p>
			</div>
		</div>";
		$this->output($content);
	}
	
	public function top()
	{
		$GLOBALS['lang']->import($GLOBALS['CONFIG']['CLASSPATH'] . '/template_on.lang');
		
		$top = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">
<html xmlns=\"http://www.w3.org/1999/xhtml\">
	<head>
		<title>{$GLOBALS['lang']['TITLE']}</title>
		<meta name=\"description\" content=\"{$GLOBALS['lang']['DESCRIPTION']}\" />
		<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />
		<meta name=\"viewport\" content=\"width=device-width; initial-scale=1.0; maximum-scale=1.0; user-scalable=0;\">
		<link rel=\"shortcut icon\" href=\"https://hosting.olympe.in/{$GLOBALS['CONFIG']['SITE']}/images/favicon.ico\" />
		<link href=\"/{$GLOBALS['CONFIG']['SITE']}/css/main.css\" rel=\"stylesheet\" type=\"text/css\" />
		<link href=\"https://fonts.googleapis.com/css?family=Cuprum\" rel=\"stylesheet\" type=\"text/css\" />
		<script type=\"text/javascript\" src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.7/jquery.min.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/spinner/jquery.mousewheel.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/spinner/ui.spinner.js\"></script>
		<script type=\"text/javascript\" src=\"https://ajax.googleapis.com/ajax/libs/jqueryui/1.8/jquery-ui.min.js\"></script> 
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/wysiwyg/jquery.wysiwyg.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/wysiwyg/wysiwyg.image.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/wysiwyg/wysiwyg.link.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/wysiwyg/wysiwyg.table.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/flot/jquery.flot.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/flot/jquery.flot.orderBars.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/flot/jquery.flot.pie.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/flot/excanvas.min.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/flot/jquery.flot.resize.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/tables/jquery.dataTables.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/tables/colResizable.min.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/forms/forms.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/forms/autogrowtextarea.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/forms/autotab.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/forms/jquery.validationEngine-en.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/forms/jquery.validationEngine.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/forms/jquery.dualListBox.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/forms/chosen.jquery.min.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/forms/jquery.maskedinput.min.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/forms/jquery.inputlimiter.min.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/forms/jquery.tagsinput.min.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/other/calendar.min.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/other/elfinder.min.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/uploader/plupload.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/uploader/plupload.html5.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/uploader/plupload.html4.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/uploader/jquery.plupload.queue.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/ui/jquery.progress.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/ui/jquery.jgrowl.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/ui/jquery.tipsy.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/ui/jquery.alerts.js\"></script>
		<script	type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/ui/jquery.colorpicker.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/wizards/jquery.form.wizard.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/wizards/jquery.validate.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/ui/jquery.breadcrumbs.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/ui/jquery.collapsible.min.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/ui/jquery.ToTop.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/ui/jquery.listnav.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/ui/jquery.sourcerer.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/ui/jquery.timeentry.min.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/plugins/ui/jquery.prettyPhoto.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/custom.js\"></script>
		<script type=\"text/javascript\" src=\"/{$GLOBALS['CONFIG']['SITE']}/js/charts/chart.js\"></script>
		<script type=\"text/javascript\">var APP_SITE = '{$GLOBALS['CONFIG']['SITE']}';</script>
	</head>
	<body>
	
		<!-- Top navigation bar -->
		<div id=\"topNav\">
			<div class=\"fixed\">
				<div class=\"wrapper\">
					<div class=\"backTo\">
						<a href=\"http://www.olympe.in\" title=\"\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/topnav/website.png\" alt=\"\" /><span>{$GLOBALS['lang']['WEBSITE']}</span></a>
						<a href=\"https://projets.olympe.in/projects/infrastructure/issues\" title=\"\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/topnav/work.png\" alt=\"\" /><span>{$GLOBALS['lang']['ISSUES']}</span></a>
						<a href=\"https://monitoring.anotherservice.com/screens.php?sid=f9566f64cb9f6e10\" title=\"\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/topnav/monitoring.png\" alt=\"\" /><span>{$GLOBALS['lang']['MONIT']}</span></a>
					</div>
					
					".$this->getMainMenu()."
					
					<div class=\"fix\"></div>
				</div>
			</div>
		</div>
		
		<!-- Header -->
		<div id=\"header\" class=\"wrapper\">
			<div class=\"logo\"><a href=\"/panel\" title=\"\"><img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/logo.png\" alt=\"\" /></a></div>
			<div class=\"middleNav\">

			</div>
			<div class=\"fix\"></div>
		</div>
		
		<!-- Content wrapper -->
		<div class=\"wrapper\">
";
		$top .= $this->getSubMenu();
		return $top;
	}
	
	private function getMainMenu()
	{
		$menu_file = $GLOBALS['CONFIG']['ROOT'].$GLOBALS['CONFIG']['SITE'].'/mainmenu.inc';
		if( file_exists($menu_file) )
		{
			$menu_data = include_once($menu_file);
			$menu = "<div class=\"userNav\">
						<ul>";

			$logged = $GLOBALS['security']->hasAccess('/');
			foreach( $menu_data as $menu_item )
			{
				// check if the user has access to the target link
				$a = $GLOBALS['security']->hasAccess($menu_item['link']);
				if( ($menu_item['anonymous'] && !$logged) || (!$menu_item['anonymous'] && $a) )
				{
					$menu .= "
						<li><a href=\"{$menu_item['link']}\" title=\"\">
							<img src=\"/{$GLOBALS['CONFIG']['SITE']}/images/icons/topnav/{$menu_item['text']}.png\" alt=\"\" />
							<span>{$GLOBALS['lang'][$menu_item['text']]}</span>
						</a></li>
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
				<!-- Left navigation -->
				<div class=\"leftNav\">
					<ul id=\"menu\">
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
						<li><a href=\"{$menu_item['link']}\" title=\"\" {$active}><span class=\"{$class}\">{$GLOBALS['lang'][$menu_item['text']]}</span></a></li>
					";
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
	
	public function bottom()
	{
		$bottom = "
		</div>
		
		<!-- Footer -->
		<div id=\"footer\">
			<div class=\"wrapper\">
				<span>{$GLOBALS['lang']['COPYRIGHT']}</span>
			</div>
		</div>
<!-- Piwik -->
<script type=\"text/javascript\">
  var _paq = _paq || [];
  _paq.push([\"trackPageView\"]);
  _paq.push([\"enableLinkTracking\"]);

  (function() {
    var u=((\"https:\" == document.location.protocol) ? \"https\" : \"http\") + \"://stats.anotherservice.com/\";
    _paq.push([\"setTrackerUrl\", u+\"piwik.php\"]);
    _paq.push([\"setSiteId\", \"6\"]);
    var d=document, g=d.createElement(\"script\"), s=d.getElementsByTagName(\"script\")[0]; g.type=\"text/javascript\";
    g.defer=true; g.async=true; g.src=u+\"piwik.js\"; s.parentNode.insertBefore(g,s);
  })();
</script>
<!-- End Piwik Code -->
	</body>
</html>";
		
		return $bottom;
	}
}

?>
