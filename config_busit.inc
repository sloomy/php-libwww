<?php

$GLOBALS['CONFIG']['DEBUG'] 		= true;
$GLOBALS['CONFIG']['THROW_ERRORS'] 	= (E_ALL | E_STRICT) & ~E_NOTICE;

$domain = explode( '.', $_SERVER["HTTP_HOST"] );
$file = '/dns/' . array_pop( $domain ) . '/' . array_pop( $domain ) . '/etc/settings' . '/' . implode( '.', $domain ) . '.ini';
if( file_exists( $file ) )
{
    $conf = parse_ini_file( $file, true );
    $conf['type'] = 'file';
}
else if( file_exists( '../www.ini' ) )
{
    $conf = parse_ini_file('../www.ini', true);
    $conf['type'] = 'file';
}
	
$GLOBALS['CONFIG']['API_HOST'] 		= 'https://' . $conf['Main']['API_HOST'];
$GLOBALS['CONFIG']['API_USERNAME']	= $conf['Main']['API_USERNAME'];
$GLOBALS['CONFIG']['API_PASSWORD']	= $conf['Main']['API_TOKEN'];
$GLOBALS['CONFIG']['HOSTNAME']		= $conf['Main']['HOSTNAME'];
$GLOBALS['CONFIG']['HOSTNAME_APPS']	= $conf['Main']['HOSTNAME_APPS'];
$GLOBALS['CONFIG']['UPTIME_TOKEN']	= $conf['Main']['UPTIME_TOKEN'];
$GLOBALS['CONFIG']['DEBUG'] 		= false;
unset($conf);
unset($file);
unset($domain);

$GLOBALS['CONFIG']['DEFAULT_PAGE']		= '/default';
$GLOBALS['CONFIG']['PANEL_PAGE']		= '/panel';
$GLOBALS['CONFIG']['LOGIN_PAGE']		= '/login_action';
$GLOBALS['CONFIG']['DEFAULT_LANGUAGE']	= 'EN';

$GLOBALS['CONFIG']['MAIL_TEMPLATE'] = "
<html>
	<head>
		<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />
		<style type=\"text/css\">
			html, body {
				background-color: #f5f5f5;
				font-family: BentonSans;
				font-size: 14px;
			}
			a {
				color: #005596;
				text-decoration: none;
			}
			a:hover {
				color: #0482e4;
			}
			p {
				margin: 0 0 15px 0;
			}
			@font-face {
				font-family: \"BentonSans\";
				src: url('https://www.bus-it.com/busit/fonts/bentonsans-regular.eot');
				src:
					url('https://www.bus-it.com/busit/fonts/bentonsans-regular.ttf') format('truetype'),
					url('https://www.bus-it.com/busit/fonts/bentonsans-regular.woff') format('woff'),
					url('https://www.bus-it.com/busit/fonts/bentonsans-regular.eot?#iefix') format('embedded-opentype'),
					url('https://www.bus-it.com/busit/fonts/bentonsans-regular.svg#BentonSans') format('svg');
				font-weight: normal;
				font-style: normal;
			}
			.core {
				padding: 20px;
			}
			.header {
				width: 90%;
				height: 50px;
				margin: 0 auto;
			}
			.content {
				width: 90%;
				margin: 0 auto;
				padding: 10px;
				background-color: #ffffff;
				border: 1px solid #e5e5e5;
				margin-bottom: 10px;
			}
			.footer {
				width: 90%;
				height: 50px;
				margin: 0 auto;
				color: #9f9f9f;
				font-size: 12px;
			}
		</style>
	</head>
	
	<body>
		<div class=\"core\">
			<div class=\"header\">
				<img src=\"https://www.bus-it.com/busit/images/logo-dark.png\" alt=\"Logo Busit\" style=\"width: 100px;\" />
			</div>
			<div class=\"content\">
				{CONTENT}
			</div>
			<div class=\"footer\">
				Copyright &copy; 2014 Busit - <a href=\"https://twitter.com/Bus_IT\" class=\"normal\">Twitter</a> - <a href=\"https://facebook.com/busit.net\" class=\"normal\">Facebook</a>
			</div>
	</body>
</html>
";

?>
