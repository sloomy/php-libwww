<?php

// IF THE HOST IS AN ALIAS THEN REDIRECT TO THE VIEW PAGE
if( preg_match("/^([a-zA-Z0-9_\\.]+)(-[0-9]{1,3})?\\.bus-it\\.com/i", $_SERVER['HTTP_HOST'], $matches) )
{
	if( $matches[1] != 'www' && $matches[1] != 'panel' && $matches[1] != 'local' )
	{
		$_GET['__rewrite'] = '/instance/view';
		$_GET['alias'] = preg_replace("/[_\\-\\.]/", "", $matches[1]);
		$_GET['interface'] = substr($matches[2], 1);
	}
}

?>