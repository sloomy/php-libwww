<?php

// if the config, core or index did not load properly : exit
if( !defined('CONFIG_LOADED') || !defined('CORE_LOADED') || !defined('INIT_LOADED') )
	throw new Exception('', 500);

// =================================
// CHECK URL
// =================================
if( !isset($_GET['__rewrite']) || !preg_match("/^[a-zA-Z0-9\\/_\\-]*$/i", $_GET['__rewrite']) )
	throw new SiteException('', 400, 'URL contains invalid characters : ' . $_GET['__rewrite']);
$GLOBALS['CONFIG']['URI'] = $_GET['__rewrite'];
unset($_GET['__rewrite']);

// =================================
// FIND PAGE
// =================================
$path = $GLOBALS['CONFIG']['URI'];
$include = null;
while( strlen($path) > 0 )
{
	//$root = $GLOBALS['CONFIG']['ROOT'] . $GLOBALS['CONFIG']['SITE'] . $path;
	$root = $GLOBALS['CONFIG']['ROOT'] . $GLOBALS['CONFIG']['SITE'] . '/' . $path;

	if( file_exists($root . '.php') )
	{
		$GLOBALS['CONFIG']['PATH'] = $root;
		$GLOBALS['CONFIG']['PAGE'] = substr($root, strlen($GLOBALS['CONFIG']['ROOT'])+strlen($GLOBALS['CONFIG']['SITE']));
	
		$include = $root . '.php';
		break;
	}
	else if( is_dir($root) && file_exists($root . '/index.php') && strlen($path) > 1 )
	{
		$GLOBALS['CONFIG']['PATH'] = $root;
		$GLOBALS['CONFIG']['PAGE'] = substr($root, strlen($GLOBALS['CONFIG']['ROOT'])+strlen($GLOBALS['CONFIG']['SITE']));
	
		$include = $root . '/index.php';
		break;
	}
	else if( $path == '.' || $path == '/' )
		break;
	
	$path = dirname($path);
}

// default page
if( $include === null )
{
	$GLOBALS['CONFIG']['PATH'] = $GLOBALS['CONFIG']['ROOT'] . $GLOBALS['CONFIG']['SITE'];
	$GLOBALS['CONFIG']['PAGE'] = $GLOBALS['CONFIG']['DEFAULT_PAGE'];
	
	//$template->notfound();
	
	if( file_exists($GLOBALS['CONFIG']['PATH'].$GLOBALS['CONFIG']['DEFAULT_PAGE'].'.php') )
		$include = $GLOBALS['CONFIG']['PATH'].$GLOBALS['CONFIG']['DEFAULT_PAGE'].'.php';
	else if( is_dir($GLOBALS['CONFIG']['PATH'].$GLOBALS['CONFIG']['DEFAULT_PAGE']) && file_exists($GLOBALS['CONFIG']['PATH'].$GLOBALS['CONFIG']['DEFAULT_PAGE'].'/index.php') )
		$include = $GLOBALS['CONFIG']['PATH'].$GLOBALS['CONFIG']['DEFAULT_PAGE'].'/index.php';
	else
		throw new SiteException('', 404, 'No handler found for URI : ' . $GLOBALS['CONFIG']['URI']);
}

// =================================
// CHECK SECURITY
// =================================
try
{
	$security->requireAccess($GLOBALS['CONFIG']['PAGE']);
}
catch(Exception $e)
{
	$_SESSION['LOGIN_REDIRECT'] = $GLOBALS['CONFIG']['PAGE'];
	$_SESSION['REDIRECT_GET'] = $_GET;
	$_SESSION['REDIRECT_POST'] = $_POST;
	$_SESSION['REDIRECT_FILES'] = $_FILES;

	if( isset($GLOBALS['CONFIG']['LOGIN_PAGE']) )
		template::redirect($GLOBALS['CONFIG']['LOGIN_PAGE']);
	else
		throw new SiteException('Unaccessible page', 403, 'Not enough grants for page : ' . $GLOBALS['CONFIG']['PAGE']);
}

// =================================
// CHECK LOGIN REDIRECT
// =================================
if( isset($_SESSION['LOGIN_REDIRECT']) && $_SESSION['LOGIN_REDIRECT'] == $GLOBALS['CONFIG']['PAGE'] )
{
	unset($_SESSION['LOGIN_REDIRECT']);
	
	$_GET = array_merge($_GET, $_SESSION['REDIRECT_GET']);
	unset($_SESSION['REDIRECT_GET']);
	
	$_POST = array_merge($_POST, $_SESSION['REDIRECT_POST']);
	unset($_SESSION['REDIRECT_POST']);
	
	$_FILES = array_merge($_FILES, $_SESSION['REDIRECT_FILES']);
	unset($_SESSION['REDIRECT_FILES']);
}

// =================================
// LOAD PAGE
// =================================
define('PROPER_START', true);
$lang->import(substr($include, 0, -3).'lang');
require_once($include);

?>
