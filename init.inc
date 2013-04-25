<?php

// =================================
// START SESSION
// =================================
session_start();

// =================================
// LOAD TRANSLATOR
// =================================
$lang = new translator();
if( isset($_GET['lang']) )
	translator::setLanguage($_GET['lang']);

// =================================
// LOAD CUSTOM TEMPLATE
// =================================
if( isset($GLOBALS['CONFIG']['SITE']) && file_exists($GLOBALS['CONFIG']['CLASSPATH'].'template_'.$GLOBALS['CONFIG']['SITE'].'.inc') )
{
	$class = 'template_'.$GLOBALS['CONFIG']['SITE'];
	$template = new $class();
}
else
	$template = template::getDummyImplementation();
	
// =================================
// LOAD CUSTOM SECURITY
// =================================
if( isset($GLOBALS['CONFIG']['SITE']) && file_exists($GLOBALS['CONFIG']['CLASSPATH'].'security_'.$GLOBALS['CONFIG']['SITE'].'.inc') )
{
	$class = 'security_'.$GLOBALS['CONFIG']['SITE'];
	$security = new $class();
}
else
	$security = security::getDummyImplementation();

// =================================
// LOAD CUSTOM INIT
// =================================
if( isset($GLOBALS['CONFIG']['SITE']) && file_exists($GLOBALS['CONFIG']['CLASSPATH'].'init_'.$GLOBALS['CONFIG']['SITE'].'.inc') )
	require_once('init_'.$GLOBALS['CONFIG']['SITE'].'.inc');

define('INIT_LOADED', true);

?>