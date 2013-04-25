<?php

abstract class template
{	
	abstract public function top();
	abstract public function bottom();
	abstract public function error($e);
	
	public final function output($content)
	{
		echo $this->top();
		echo $content;
		echo $this->bottom();
		exit;
	}
	
	public final static function redirect($link)
	{
		if( preg_match("/^https?:\\/\\/.+/i", $link) )
		{
			header("Location: {$link}");
			exit;
		}
		else
		{
			$host = $_SERVER['HTTP_HOST'];
			$uri = rtrim(dirname($_SERVER['PHP_SELF']), '/\\');
			$extra = ltrim($link, '/\\');
			
			$protocol = 'http';
			//if( 1 /*isset($_SERVER['HTTP_X_SSL_CIPHER']) && $_SERVER['HTTP_X_SSL_CIPHER'] != "" && $_SERVER['HTTP_X_SSL_CIPHER'] != 'off'*/ )
			//	$protocol .= 's';

			header("Location: {$protocol}://{$host}{$uri}/{$extra}");
			exit;
		}
	}

	public final static function refresh()
	{
		$page = $_SERVER['REQUEST_URI'];
		self::redirect($page);
	}
	
	public final static function getDummyImplementation()
	{
		return new __undefinedTemplate();
	}
}

class __undefinedTemplate extends template
{
	public function top(){ return ''; }
	public function bottom(){ return ''; }
	public function error($e){ if( $GLOBALS['CONFIG']['DEBUG'] ) error_log("SENDING HEADER 500 : Error handler of default template in template.inc"); header("HTTP/1.0 500 Internal Server Error"); exit; }
}
?>
