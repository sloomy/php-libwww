<?php

$GLOBALS['CONFIG']['DEBUG'] 		= true;
$GLOBALS['CONFIG']['THROW_ERRORS'] 	= (E_ALL | E_STRICT) & ~E_NOTICE;

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
