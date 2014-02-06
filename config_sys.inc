<?php

$GLOBALS['CONFIG']['DEBUG'] 		= true;
$GLOBALS['CONFIG']['THROW_ERRORS'] 	= (E_ALL | E_STRICT) & ~E_NOTICE;

if( $_SERVER["HTTP_HOST"] == 'localhost' || $_SERVER["HTTP_HOST"] == '127.0.0.1' || $_SERVER["HTTP_HOST"] == 'local.sys.as' )
	$conf = parse_ini_file('../www.ini', true);
elseif( $_SERVER["HTTP_HOST"] == 'dev.sys.as' || $_SERVER["HTTP_HOST"] == 'www.dev.sys.as' )
	$conf = parse_ini_file('/dns/as/sys/etc/settings/www.dev.ini', true);
else
	$conf = parse_ini_file('/dns/as/sys/etc/settings/www.ini', true);
	
$GLOBALS['CONFIG']['API_AS_HOST'] 		= 'https://' . $conf['Main']['API_AS_HOST'];
$GLOBALS['CONFIG']['API_AS_USERNAME']	= $conf['Main']['API_AS_USERNAME'];
$GLOBALS['CONFIG']['API_AS_PASSWORD']	= $conf['Main']['API_AS_TOKEN'];
$GLOBALS['CONFIG']['API_ON_HOST'] 		= 'https://' . $conf['Main']['API_ON_HOST'];
$GLOBALS['CONFIG']['API_ON_USERNAME']	= $conf['Main']['API_ON_USERNAME'];
$GLOBALS['CONFIG']['API_ON_PASSWORD']	= $conf['Main']['API_ON_TOKEN'];
$GLOBALS['CONFIG']['API_BI_HOST'] 		= 'https://' . $conf['Main']['API_BI_HOST'];
$GLOBALS['CONFIG']['API_BI_USERNAME']	= $conf['Main']['API_BI_USERNAME'];
$GLOBALS['CONFIG']['API_BI_PASSWORD']	= $conf['Main']['API_BI_TOKEN'];
$GLOBALS['CONFIG']['HOSTNAME']		= $conf['Main']['HOSTNAME'];
$GLOBALS['CONFIG']['UPTIME_TOKEN']	= $conf['Main']['UPTIME_TOKEN'];

if( $conf['Main']['DEBUG'] == 'inactive' )
$GLOBALS['CONFIG']['DEBUG'] 		= false;
unset($conf);

$GLOBALS['CONFIG']['DEFAULT_PAGE']		= '/default';
$GLOBALS['CONFIG']['PANEL_PAGE']		= '/panel';
$GLOBALS['CONFIG']['LOGIN_PAGE']		= '/?elogin';
$GLOBALS['CONFIG']['DEFAULT_LANGUAGE']	= 'FR';

$GLOBALS['CONFIG']['MAIL_TEMPLATE'] = "
<html>
<head>
	<title>Another Service</title>
	<style type=\"text/css\">
		html, body {
			background-color: #e5e9ee;
		}

		body {
			margin: 0;
			font-family: Arial;
			font-size: 15px;
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
		
		h1 {
			font-size: 20px;
			font-weight: bold;
		}

		h2 {
			font-size: 17px;
			font-weight: bold;	
		}
		
		.btn {
			display: inline-block;
			padding: 4px 17px 3px;
			margin: 0px 7px 4px 0;
			font-size: 14px;
			line-height: 21px;
			color: #585858;
			text-align: center;
			text-shadow: 0 1px 1px rgba(255, 255, 255, 0.75);
			-webkit-border-radius: 20px;
			-moz-border-radius: 20px;
			border-radius: 20px;
			-webkit-border-radius: 20px;
			-moz-border-radius: 20px;
			border-radius: 20px;
			border-radius: 20px;
			-moz-border-radius: 20px;
			-webkit-border-radius: 20px;
			cursor: pointer;
			background-color: #f1f1f1;
			background-image: -moz-linear-gradient(top, #f8f8f8, #e7e7e7);
			background-image: -ms-linear-gradient(top, #f8f8f8, #e7e7e7);
			background-image: -webkit-gradient(linear, 0 0, 0 100%, from(#f8f8f8), to(#e7e7e7));
			background-image: -webkit-linear-gradient(top, #f8f8f8, #e7e7e7);
			background-image: -o-linear-gradient(top, #f8f8f8, #e7e7e7);
			background-image: linear-gradient(top, #f8f8f8, #e7e7e7);
			background-repeat: repeat-x;
			filter: progid:DXImageTransform.Microsoft.gradient(startColorstr='#f8f8f8', endColorstr='#e7e7e7', GradientType=0);
			background-color: #f1f1f1;
			background-image: -moz-linear-gradient(top, #f8f8f8, #e7e7e7);
			background-image: -ms-linear-gradient(top, #f8f8f8, #e7e7e7);
			background-image: -webkit-gradient(linear, 0 0, 0 100%, from(#f8f8f8), to(#e7e7e7));
			background-image: -webkit-linear-gradient(top, #f8f8f8, #e7e7e7);
			background-image: -o-linear-gradient(top, #f8f8f8, #e7e7e7);
			background-image: linear-gradient(top, #f8f8f8, #e7e7e7);
			background-repeat: repeat-x;
			filter: progid:DXImageTransform.Microsoft.gradient(startColorstr='#f8f8f8', endColorstr='#e7e7e7', GradientType=0);
			/*  @shadow: inset 0 1px 0 rgba(255,255,255,.25), 0 1px 0px rgba(255,255,255,0.5);*/

			-webkit-box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.25), 0 1px 3px rgba(0, 0, 0, 0.2);
			-moz-box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.25), 0 1px 3px rgba(0, 0, 0, 0.2);
			box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.25), 0 1px 3px rgba(0, 0, 0, 0.2);
			-webkit-box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.25), 0 1px 3px rgba(0, 0, 0, 0.2);
			-moz-box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.25), 0 1px 3px rgba(0, 0, 0, 0.2);
			box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.25), 0 1px 3px rgba(0, 0, 0, 0.2);
			border: 1px solid #c9ccd0;
			*margin-left: .3em;
			*margin-left: .3em;
		}
	</style>
</head>
<body>
	<div style=\"background-color: #000000; width: 100%; height: 60px; padding: 20px 10px 10px 10px; margin-bottom: 20px; text-align: center;\">
		<img src=\"https://www.anotherservice.com/as/images/logo.png\" alt=\"\" />
	</div>
	<div style=\"padding: 10px; width: 600px; margin: 0 auto; border: 1px solid #a1a1a1;\">
		<div style=\"\">
			<h1>{TITLE}</h1>
			{CONTENT}
		</div>
		<br /><br />
		<div style=\"float: left;\">
			<strong>S.Y.S. SAS - Another Service</strong><br />
			<a href=\"https://www.anotherservice.com\">https://www.anotherservice.com</a><br />
			<a href=\"mailto: contact@anotherservice.com\">contact@anotherservice.com</a>
		</div>
		<div style=\"float: right;\">
			<strong>Support technique</strong><br />
			<a href=\"https://support.anotherservice.com/projects/global-support\">https://support.anotherservice.com</a><br />
			<a href=\"mailto: support@anotherservice.com\">support@anotherservice.com</a>
		</div>
		<div style=\"clear: both; padding: 2px;\"></div>
	</div>
</body>
</html>";

?>
