<?php

$GLOBALS['CONFIG']['DEBUG'] 		= true;
$GLOBALS['CONFIG']['THROW_ERRORS'] 	= (E_ALL | E_STRICT) & ~E_NOTICE;

if( $_SERVER["HTTP_HOST"] == 'localhost' || $_SERVER["HTTP_HOST"] == '127.0.0.1' || $_SERVER["HTTP_HOST"] == 'local.anotherservice.com' )
	$conf = parse_ini_file('../www.ini', true);
elseif( $_SERVER["HTTP_HOST"] == 'dev.anotherservice.com' || $_SERVER["HTTP_HOST"] == 'www.dev.anotherservice.com' )
	$conf = parse_ini_file('/dns/com/anotherservice/etc/settings/www.dev.ini', true);
else
	$conf = parse_ini_file('/dns/com/anotherservice/etc/settings/www.ini', true);
	
$GLOBALS['CONFIG']['API_HOST'] 		= 'https://' . $conf['Main']['API_HOST'];
$GLOBALS['CONFIG']['API_USERNAME']	= $conf['Main']['API_USERNAME'];
$GLOBALS['CONFIG']['API_PASSWORD']	= $conf['Main']['API_TOKEN'];

if( $conf['Main']['DEBUG'] == 'inactive' )
$GLOBALS['CONFIG']['DEBUG'] 		= false;
unset($conf);

$GLOBALS['CONFIG']['DEFAULT_PAGE']		= '/default';
$GLOBALS['CONFIG']['PANEL_PAGE']		= '/panel';
$GLOBALS['CONFIG']['LOGIN_PAGE']		= '/login';
$GLOBALS['CONFIG']['DEFAULT_LANGUAGE']	= 'FR';

$GLOBALS['CONFIG']['MAIL_TEMPLATE'] = "
<html>
<head>
	<title>Bus IT</title>
	<style>
		html, body {
			background-color: #e5e9ee;
		}

		body {
			margin: 0;
			font-family: \"Helvetica Neue\", Helvetica, Arial, sans-serif;
			font-size: 13px;
			font-weight: normal;
			line-height: 18px;
			color: #404040;
		}

		a {
			color: #2e9fff;
			text-decoration: none;
			-webkit-transition: all 0.2s;
			-moz-transition: all 0.2s;
			-ms-transition: all 0.2s;
			-o-transition: all 0.2s;
			transition: all 0.2s;
		}

		a:hover {
			color: #0079e1;
		}
	</style>
</head>
<body>
	<div style=\"background-color: #477196; width: 100%; height: 30px; color: #ffffff; font-size: 20px; padding: 10px; margin-bottom: 20px;\">
		Bus IT :: {TITLE}
	</div>
	<div style=\"padding: 10px;\">
		{CONTENT}
	</div>
</body>
</html>";

?>
