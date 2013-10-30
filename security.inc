<?php

abstract class security
{
	abstract public function login($user = '', $pass = '', $save = false);
	public function logout() { unset($_SESSION['SECURITY'][$GLOBALS['CONFIG']['SITE']]); }
	
	public static function set($key, $value) { $_SESSION['SECURITY'][$GLOBALS['CONFIG']['SITE']]['__VARIABLES'][$key] = $value; }
	public static function get($key) { return $_SESSION['SECURITY'][$GLOBALS['CONFIG']['SITE']]['__VARIABLES'][$key]; }
	
	public static function hasGrant($grant)
	{
		if( !is_array($grant) )
			$grant = array($grant);
		
		if( !isset($_SESSION['SECURITY'][$GLOBALS['CONFIG']['SITE']]['__GRANTS']) )
			return false;

		foreach( $grant as $g )
			if( !in_array($g, $_SESSION['SECURITY'][$GLOBALS['CONFIG']['SITE']]['__GRANTS']) )
				return false;
		
		return true;
	}
	
	public static function requireGrant($grant)
	{
		if( !self::hasGrant($grant) )
			throw new SiteException('Unsufficient permission', 403, 'Not all grants available : ' . print_r($grant));
	}
	
	public static function setGrant($grant)
	{
		if( !is_array($grant) )
			$grant = array($grant);
		
		foreach( $grant as $g )
			if( !self::hasGrant($g) )
				$_SESSION['SECURITY'][$GLOBALS['CONFIG']['SITE']]['__GRANTS'][] = $g;
	}
	
	public static function clearGrant($grant=null)
	{
		if( $grant == null )
		{
			$_SESSION['SECURITY'][$GLOBALS['CONFIG']['SITE']]['__GRANTS'] = array();
			return;
		}
		
		if( !is_array($grant) )
			$grant = array($grant);
		
		foreach( $grant as $g )
		{
			$index = array_search($g, $_SESSION['SECURITY'][$GLOBALS['CONFIG']['SITE']]['__GRANTS']);
			if( $index !== false )
				array_splice($_SESSION['SECURITY'][$GLOBALS['CONFIG']['SITE']]['__GRANTS'], $index, 1);
		}
	}
	
	public static function encode($text, $escapeslashes = true, $html = false)
	{
		// WARNING : mysql NEEDS escaped \'s so we assume that $escapeslashes is true by default.
		// Thus we ADD the \ if it is not set by the magic_quotes_gpc.
		// If explicitrly specified, we can strip the escaped \'s by the magic_quotes_gpc()
			
		// returns a SQL safe text with html line breaks
		if( get_magic_quotes_gpc() && !$escapeslashes )
			$text = stripslashes($text);
		if( !get_magic_quotes_gpc() && $escapeslashes )
			$text = addslashes($text);
		
		if( $html )
			return preg_replace('/\s\s+/', ' ',nl2br(htmlentities(trim($text),ENT_QUOTES, 'UTF-8')));
		else
			return trim($text);
	}
	
	public static final function getDummyImplementation()
	{
		return new __undefinedSecurity();
	}
}

class __undefinedSecurity extends security
{
	public function login($user = '', $pass = '', $save = false) { }
}
?>