<?php

class translator implements ArrayAccess
{
	private $data = array();
	const COOKIE_VAR = 'language';
	
	public function __construct($language = null)
	{
		if( $language != null )
			self::setLanguage($language);
		else if( isset($_SESSION['CONFIG']['LANGUAGE']) )
			self::setLanguage($_SESSION['CONFIG']['LANGUAGE']);
		else if( isset($_COOKIE[self::COOKIE_VAR]) )
			self::setLanguage($_COOKIE[self::COOKIE_VAR]);
		else if( !isset($GLOBALS['CONFIG']['LANGUAGE']) )
		{
			if( substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2) == 'fr' )
				self::setLanguage('FR');
			else if( substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2) == 'es' )
				self::setLanguage('ES');
			else if( substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2) == 'en' )
				self::setLanguage('EN');
			else if( substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2) == 'de' )
				self::setLanguage('DE');
			else if( substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2) == 'it' )
				self::setLanguage('IT');
			else
				self::setLanguage($GLOBALS['CONFIG']['DEFAULT_LANGUAGE']);
		}
	}

	public function import($filename)
	{
		if( !preg_match("/^(\\/|[A-Z]:)/", $filename) )
		{
			if( !preg_match("/.+\\.lang$/i", $filename) )
				$filename .= '.lang';
				
			$filename = $GLOBALS['CONFIG']['PATH'] . $filename;
		}

		if( !file_exists($filename) )
			return;

		$new_data = parse_ini_file( $filename, true );

		foreach($new_data as $key=>$value)
		{
			if( is_array($value) ) // language containing translation
			{
				if( isset($this->data[strtoupper($key)]) ) // language exists -> merge
					$this->data[strtoupper($key)] = array_merge($this->data[strtoupper($key)], $value);
				else // language does not exist -> assign
					$this->data[strtoupper($key)] = $value;
			}
			else // direct translation
			{
				$this->data[$GLOBALS['CONFIG']['LANGUAGE']][strtoupper($key)] = $value;
			}
		}
	}
	
	public static function setLanguage($language)
	{
		$GLOBALS['CONFIG']['LANGUAGE'] = strtoupper($language);
		
		if( isset($_SESSION) )
			$_SESSION['CONFIG']['LANGUAGE'] = strtoupper($language);
		
		if( !headers_sent() )
			setcookie(self::COOKIE_VAR, strtoupper($language), mktime(0,0,0,12,31,2030), '/');
	}
	
	public static function getLanguage()
	{
		if( isset($_SESSION['CONFIG']['LANGUAGE']) )
			return strtoupper($_SESSION['CONFIG']['LANGUAGE']);
		else if( isset($_COOKIE[self::COOKIE_VAR]) )
			return strtoupper($_COOKIE[self::COOKIE_VAR]);
		else if( isset($GLOBALS['CONFIG']['LANGUAGE']) )
			return strtoupper($GLOBALS['CONFIG']['LANGUAGE']);
		else
			return strtoupper($GLOBALS['CONFIG']['DEFAULT_LANGUAGE']);
	}

	// do NOT remove this function
	public function offsetExists ( $index )
	{
		$l = strtoupper($GLOBALS['CONFIG']['LANGUAGE']);
		return isset( $this->data[$l][$index] );
	}
	
	// do NOT remove this function
	public function offsetUnset ( $index )
	{
		$l = strtoupper($GLOBALS['CONFIG']['LANGUAGE']);
		if( isset($this->data[$l][$index]) )
			unset($this->data[$l][$index]);
	}
	
	// do NOT remove this function
	public function offsetGet ( $index )
	{
		$l = strtoupper($GLOBALS['CONFIG']['LANGUAGE']);
		if( isset($this->data[$l][$index]) )
			return $this->data[$l][$index];
		else
		{
			foreach($this->data as $language)
				if( isset($language[$index]) )
					return $language[$index];
			
			return "";
		}
	}
	
	// do NOT remove this function
	public function offsetSet ( $index, $newval )
	{
		$l = strtoupper($GLOBALS['CONFIG']['LANGUAGE']);
		if( is_array($newval) )
			foreach($newval as $language => $val )
				$this->data[strtoupper($language)][$index] = $val;
		else
			$this->data[$l][$index] = $newval;
	}

	public function get ( $index, $language )
	{
		$language = strtoupper($language);
		if( isset($this->data[$language][$index]) )
			return $this->data[$language][$index];
		else
		{
			foreach($this->data as $l)
				if( isset($l[$index]) )
					return $l[$index];
			
			return "";
		}
	}
	
	public static function extract($text, $default = 'en')
	{
		preg_match_all("/<!--:([a-z]+)-->(.*?)<!--:-->/s", $text, $matches, PREG_SET_ORDER);
		$candidate = null;
		
		if( count($matches) > 0 )
		{
			foreach( $matches as $m )
			{
				if( $m[1] == strtolower(self::getLanguage()) )
					return $m[2];
				if( $m[1] == $default )
					$candidate = $m[2];
			}
			if( $candidate === null )
				$candidate = $matches[0][2];
		}
		else
			$candidate = $text;
 
		return $candidate;
	}
}

?>