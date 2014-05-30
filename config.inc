<?php

// =================================
// CROSSDOMAIN
// =================================
if( preg_match("/^\\/?crossdomain.xml$/i", $_GET['__rewrite']) )
{
	header("Content-Type: text/xml");
	echo "<?xml version=\"1.0\"?><cross-domain-policy><allow-access-from domain=\"*\"/><site-control permitted-cross-domain-policies=\"all\"/><allow-http-request-headers-from domain=\"*\" headers=\"*\"/></cross-domain-policy>";
	exit;
}

// =================================
// DEFAULT PARAMETERS (OVERRIDE IN SITE CONFIG)
// =================================
$GLOBALS['CONFIG'] 						= array();
$GLOBALS['CONFIG']['CLASSPATH'] 		= __DIR__ . '/';
$GLOBALS['CONFIG']['ROOT'] 				= dirname($GLOBALS['CONFIG']['CLASSPATH']) . '/';
$GLOBALS['CONFIG']['DEBUG'] 			= false;
$GLOBALS['CONFIG']['THROW_ERRORS'] 		= 0;
$GLOBALS['CONFIG']['LOGIN_PAGE']        = 'user/login';
$GLOBALS['CONFIG']['FORCE_FIRST_TOKEN']	= true;
$GLOBALS['CONFIG']['DEFAULT_LANGUAGE']  = 'EN';

// =================================
// DETECT CURRENT SITE
// =================================
$domain = explode ( '.', $_SERVER["HTTP_HOST"] );
$tld = array_pop( $domain );
$host = array_pop( $domain ) . '.' . $tld;
$sub = array_shift( $domain );

// SPECIAL CASE FOR BUSIT ALIAS :

if( preg_match("/\\.bus-it\\.com$/i", $_SERVER['HTTP_HOST']) && !preg_match("/^(apps|local|developers|www)\\./i", $_SERVER['HTTP_HOST']) )
{
	$GLOBALS['CONFIG']['SITE'] = 'busit';
	$GLOBALS['CONFIG']['INSTANCE'] = true;
}
else

switch( $host )
{
	case 'olympe.in':
		$GLOBALS['CONFIG']['SITE'] = 'on';
		break;
	case 'anotherservice.com':
	case 'another.io':
		$GLOBALS['CONFIG']['SITE'] = 'as';
		break;
	case 'sys.as':
	case 'sys.sas':
	case 'sys.fr':
	case 'sys.com':
		$GLOBALS['CONFIG']['SITE'] = 'sys';
		break;
	case 'bus-it.com':
	case 'bus-it.net':
        if ($sub == 'apps')
		    $GLOBALS['CONFIG']['SITE'] = 'apps';
        else
            $GLOBALS['CONFIG']['SITE'] = 'busit';
        if( !preg_match("/^(apps|local|developers|www)/i", $sub) )
        {
            $GLOBALS['CONFIG']['INSTANCE'] = true;
        }
		break;
	default:
		if( $GLOBALS['CONFIG']['DEBUG'] )
			error_log("SENDING HEADER 500 : No site defined in config.inc");
		header("HTTP/1.0 500 Internal Server Error");
		exit;
}

// =================================
// LOAD CUSTOM CONFIG
// =================================
if( isset($GLOBALS['CONFIG']['SITE']) && file_exists($GLOBALS['CONFIG']['CLASSPATH'].'config_'.$GLOBALS['CONFIG']['SITE'].'.inc') )
	require_once($GLOBALS['CONFIG']['CLASSPATH'].'config_'.$GLOBALS['CONFIG']['SITE'].'.inc');

define('CONFIG_LOADED', true);

?>
