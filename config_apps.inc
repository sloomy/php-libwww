<?php

$GLOBALS['CONFIG']['DEBUG'] 		= true;
$GLOBALS['CONFIG']['THROW_ERRORS'] 	= (E_ALL | E_STRICT) & ~E_NOTICE;

if( $_SERVER["HTTP_HOST"] == 'localhost' || $_SERVER["HTTP_HOST"] == '127.0.0.1' || $_SERVER["HTTP_HOST"] == 'local.apps.bus-it.com' )
	$conf = parse_ini_file('../www.ini', true);
else
	$conf = parse_ini_file('/dns/com/bus-it/etc/settings/www.ini', true);

$GLOBALS['CONFIG']['API_HOST'] 		= 'https://' . $conf['Main']['API_HOST'];
$GLOBALS['CONFIG']['API_USERNAME']	= $conf['Main']['API_USERNAME'];
$GLOBALS['CONFIG']['API_PASSWORD']	= $conf['Main']['API_TOKEN'];
$GLOBALS['CONFIG']['HOSTNAME']		= $conf['Main']['HOSTNAME'];
$GLOBALS['CONFIG']['HOSTNAME_APPS']	= $conf['Main']['HOSTNAME_APPS'];
$GLOBALS['CONFIG']['DEBUG'] 		= false;
unset($conf);

$GLOBALS['CONFIG']['DEFAULT_PAGE']		= '/default';
$GLOBALS['CONFIG']['PANEL_PAGE']		= '/panel';
$GLOBALS['CONFIG']['LOGIN_PAGE']		= '/login';
$GLOBALS['CONFIG']['DEFAULT_LANGUAGE']	= 'EN';

?>