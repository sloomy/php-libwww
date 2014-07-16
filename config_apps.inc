<?php

$GLOBALS['CONFIG']['DEBUG'] 		= true;
$GLOBALS['CONFIG']['THROW_ERRORS'] 	= (E_ALL | E_STRICT) & ~E_NOTICE;

$domain = explode( '.', $_SERVER["HTTP_HOST"] );
$dir .= '/dns/' . array_pop( $domain ) . '/' . array_pop( $domain ) . '/etc/settings';
$file = $dir . '/' . implode( '.', $domain ) . '.ini';
if( file_exists( $file ) )
{
    $conf = parse_ini_file( $file, true );
    $conf['type'] = 'file';
}
else if( file_exists( '../www.ini' ) )
{
    $conf = parse_ini_file('../www.ini');
    $conf['type'] = 'file';
}

$GLOBALS['CONFIG']['API_HOST'] 		= 'https://' . $conf['Main']['API_HOST'];
$GLOBALS['CONFIG']['API_USERNAME']	= $conf['Main']['API_USERNAME'];
$GLOBALS['CONFIG']['API_PASSWORD']	= $conf['Main']['API_TOKEN'];
$GLOBALS['CONFIG']['HOSTNAME']		= $conf['Main']['HOSTNAME'];
$GLOBALS['CONFIG']['HOSTNAME_APPS']	= $conf['Main']['HOSTNAME_APPS'];
$GLOBALS['CONFIG']['DEBUG'] 		= false;
unset($conf);
unset($file);
unset($domain);

$GLOBALS['CONFIG']['DEFAULT_PAGE']		= '/default';
$GLOBALS['CONFIG']['PANEL_PAGE']		= '/panel';
$GLOBALS['CONFIG']['LOGIN_PAGE']		= '/login';
$GLOBALS['CONFIG']['DEFAULT_LANGUAGE']	= 'EN';

?>
