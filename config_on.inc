<?php

$GLOBALS['CONFIG']['DEBUG'] 		= true;
$GLOBALS['CONFIG']['THROW_ERRORS'] 	= (E_ALL | E_STRICT) & ~E_NOTICE;

if( $_SERVER["HTTP_HOST"] == 'localhost' || $_SERVER["HTTP_HOST"] == '127.0.0.1' || $_SERVER["HTTP_HOST"] == 'local.hosting.olympe.in' )
	$conf = parse_ini_file('../hosting.ini', true);
elseif( $_SERVER["HTTP_HOST"] == 'hosting.dev.olympe.in' )
	$conf = parse_ini_file('/dns/in/olympe/etc/settings/hosting.dev.ini', true);
else
	$conf = parse_ini_file('/dns/in/olympe/etc/settings/hosting.ini', true);

$GLOBALS['CONFIG']['API_HOST'] 		= 'https://' . $conf['Main']['API_HOST'];
$GLOBALS['CONFIG']['API_USERNAME']	= $conf['Main']['API_USERNAME'];
$GLOBALS['CONFIG']['API_PASSWORD']	= $conf['Main']['API_TOKEN'];
if( $conf['Main']['DEBUG'] == 'inactive' )
	$GLOBALS['CONFIG']['DEBUG'] 		= false;
unset($conf);

$GLOBALS['CONFIG']['DEFAULT_PAGE']		= '/panel';
$GLOBALS['CONFIG']['LOGIN_PAGE']		= '/login';
$GLOBALS['CONFIG']['DEFAULT_LANGUAGE']	= 'FR';

?>
