<?php

class template_apps extends template
{
	public function __construct()
	{
		$GLOBALS['lang']->import($GLOBALS['CONFIG']['CLASSPATH'] . '/template_apps.lang');
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
		<link rel=\"shortcut icon\" href=\"/busit/images/favicon.ico\" />
		<link rel=\"stylesheet\" href=\"/busit/css/main.css\" type=\"text/css\" />
		<link rel=\"stylesheet\" href=\"/busit/css/font-awesome.css\" type=\"text/css\" />
		<link rel=\"stylesheet\" href=\"/busit/css/jquery-1.10.4/jquery-ui-1.10.4.custom.min.css\" />
		<link rel=\"stylesheet\" href=\"/busit/css/jquery-1.10.4/default.css\" />
		<link href=\"https://fonts.googleapis.com/css?family=Cuprum\" rel=\"stylesheet\" type=\"text/css\" />
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-2.1.1.min.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-globalize.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-ui-1.10.4.custom.min.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-ui-touch-punch.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-ui-timepicker.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-chartjs.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-raty.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-jsplumb.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-sceditor.bbcode.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-toggles.js\"></script>";
	$top .= "
	</head>
	<body>
		<div id=\"apps\" style=\"width: 90%; margin: 0 auto;\">
			";
		
		return $top;
	}
	
	public function bottom()
	{
		$bottom = "";
		$bottom .= "	
		</div>
	</body>
</html>";
		
		return $bottom;
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
		<link rel=\"shortcut icon\" href=\"/busit/images/favicon.ico\" />
		<link rel=\"stylesheet\" href=\"/busit/css/main.css\" type=\"text/css\" />
		<link rel=\"stylesheet\" href=\"/busit/css/font-awesome.css\" type=\"text/css\" />
		<link rel=\"stylesheet\" href=\"/busit/css/jquery-1.10.4/jquery-ui-1.10.4.custom.min.css\" />
		<link rel=\"stylesheet\" href=\"/busit/css/jquery-1.10.4/default.css\" />
		<link href=\"https://fonts.googleapis.com/css?family=Cuprum\" rel=\"stylesheet\" type=\"text/css\" />
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-2.1.1.min.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-globalize.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-ui-1.10.4.custom.min.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-ui-touch-punch.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-ui-timepicker.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-chartjs.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-raty.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-jsplumb.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-sceditor.bbcode.js\"></script>
		<script type=\"text/javascript\" src=\"/busit/js/jquery/jquery-toggles.js\"></script>
	$top .= "
	</head>
	<body>
			";
		
		return $top;
	}
	
	public function bottomSimple()
	{
		$bottom = "";
		$bottom .= "	
	</body>
</html>";
		
		return $bottom;
	}
}

?>