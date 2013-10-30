<?php
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * COPYRIGHT INFORMATION
 * This class is part of a website framework developped by
 * Simon UYTTENDAELE. It may be used, copied, modified, and
 * redistributed only for non-commercial activities.
 * 
 * This copyright notice should remain visible on top of every file.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* CLASS INFORMATION

- Description:
	This class manages custom bbcode encoding / decoding / display.

- Usage:
	All functions are static, to use them, simply call 'bbcode::display', 'bbcode::encode' or
	'bbcode::edit'.
*/

class bbcode
{
	const BBCODE = 1;
	const WIKI = 2;
	
	public static function display($txt, $mode = self::BBCODE)
	{
		$search = array();
		
		// converts a bbcode text to HTML display
		if( $mode == self::BBCODE )
		{
			$search = array(
				'/\[b\](.*?)\[\/b\]/is',                                
				'/\[i\](.*?)\[\/i\]/is',                                
				'/\[u\](.*?)\[\/u\]/is',
				'/\[s\](.*?)\[\/s\]/is',
				'/\[color\=(.*?)\](.*?)\[\/color\]/is',
				'/\[small\](.*?)\[\/small\]/is',
				'/\[big\](.*?)\[\/big\]/is',
				'/\[tab\]/i',
				'/\[br\]/i',
				'/\[code\](.*?)\[\/code\]/is',
				'/\[quote\](.*?)\[\/quote\]/is',
				'/\[img\](.*?)\[\/img\]/is',
				'/\[link\=(.*?)\](.*?)\[\/link\]|\[url\](.*?)\[\/url\]|(\s+https?:\/\/[^\s\[<>"]*)/is'
				);
		}
		else if( $mode == self::WIKI )
		{
			$search = array(
				'/(^|\s)\*(\S|\S.*?\S)\*(\s|$)/is',                                
				'/(^|\s)_(\S|\S.*?\S)_(\s|$)/is',                                
				'/(^|\s)\+(\S|\S.*?\S)\+(\s|$)/is',
				'/(^|\s)-(\S|\S.*?\S)-(\s|$)/is',
				'/(^|\s)>(\s|$)/',
				'/(^|\s)@(\S|\S.*?\S)@(\s|$)/is',
				'/(^|\s)\?\?(\S|\S.*?\S)\?\?(\s|$)/is',
				'/(^|\s)!(\S|\S.*?\S)!(\s|$)/is',
				'/"(.*?)":(https?:\/\/\S*?)/is',
				'/(\r\n|\r|\n)/i'
				);
		}

        $replace = array();
		
		if( $mode == self::BBCODE )
		{
			$replace = array(
				'<strong>$1</strong>',
				'<em>$1</em>',
				'<span style="text-decoration:underline;">$1</span>',
				'<span style="text-decoration:line-through;">$1</span>',
				'<span style="color:$1;">$2</span>',
				'<span style="font-size:0.7em;">$1</span>',
				'<span style="font-size:1.3em;">$1</span>',
				'<span style="margin-right:25px;"> </span>',
				'<br />',
				'<div class="forum_code">$1<br />&nbsp;</div>',
				'<div class="forum_quote">$1<br />&nbsp;</div>',
				'<img src="$1" alt="" style="float:left; max-width: 670px;" />',
				'<a href="$1$3$4">$2$3$4</a>'
				);
		}
		else if( $mode == self::WIKI )
		{
			$replace = array(
				'$1<strong>$2</strong>$3',
				'$1<em>$2</em>$3',
				'$1<span style="text-decoration:underline;">$2</span>$3',
				'$1<span style="text-decoration:line-through;">$2</span>$3',
				'$1<span style="margin-right:25px;"> </span>$2',
				'$1<div class="forum_code">$2<br />&nbsp;</div>$3',
				'$1<div class="forum_quote">$2<br />&nbsp;</div>$3',
				'$1<img src="$2" alt="" style="float:left;" />$3',
				'<a href="$2">$1</a>',
				'<br />'
				);
		}
		
		return preg_replace($search, $replace, $txt);
	}
	
	public static function edit($txt, $mode = self::BBCODE)
	{
		// converts a bbcode text to an editable textfield value
		$search = array();
		$replace = array();
		
		if( $mode == self::BBCODE )
		{
			$search = array('/\[br\]/', '/\[tab\]/');
			$replace = array("\n", '    ');
		}
		
		return preg_replace($search, $replace, $txt);
	}
	
	public static function convert($txt, $from = self::BBCODE, $to = self::WIKI)
	{
		$search = array();
		
		// converts a bbcode text to HTML display
		if( $from == self::BBCODE )
		{
			$search = array(
				'/\[b\](.*?)\[\/b\]/is',                                
				'/\[i\](.*?)\[\/i\]/is',                                
				'/\[u\](.*?)\[\/u\]/is',
				'/\[s\](.*?)\[\/s\]/is',
				'/\[tab\]/i',
				'/\[code\](.*?)\[\/code\]/is',
				'/\[quote\](.*?)\[\/quote\]/is',
				'/\[img\](.*?)\[\/img\]/is',
				'/\[link\=(.*?)\](.*?)\[\/link\]/is'
				);
		}
		else if( $from == self::WIKI )
		{
			$search = array(
				'/(^|\s)\*(\S|\S.*?\S)\*(\s|$)/is',                                
				'/(^|\s)_(\S|\S.*?\S)_(\s|$)/is',                                
				'/(^|\s)\+(\S|\S.*?\S)\+(\s|$)/is',
				'/(^|\s)-(\S|\S.*?\S)-(\s|$)/is',
				'/(^|\s)>(\s|$)/',
				'/(^|\s)@(\S|\S.*?\S)@(\s|$)/is',
				'/(^|\s)\?\?(\S|\S.*?\S)\?\?(\s|$)/is',
				'/(^|\s)!(\S|\S.*?\S)!(\s|$)/is',
				'/"(.*?)":(https?:\/\/\S*?)/is'
				);
		}

        $replace = array();
		
		if( $to == self::BBCODE )
		{
			$replace = array(
				'$1[b]$2[/b]$3',
				'$1[i]$2[/i]$3',
				'$1[u]$2[/u]$3',
				'$1[s]$2[/s]$3',
				'$1[tab]$2',
				'$1[code]$2[/code]$3',
				'$1[quote]$2[/quote]$3',
				'$1[img]$2[/img]$3',
				'[link=$2]$1[/link]'
				);
		}
		else if( $to == self::WIKI )
		{
			$replace = array(
				' *$1* ',
				' _$1_ ',
				' +$1+ ',
				' -$1- ',
				'> ',
				' @$1@ ',
				' ??$1?? ',
				' !$1! ',
				'"$2":$1'
				);
		}
		
		return preg_replace($search, $replace, $txt);
	}
	
	public static function encode($txt, $mode = self::BBCODE, $escape = true)
	{
		if( $mode == self::BBCODE )
		{
			$search = array('/\r/', '/\n/', '/\t/', '/\s{3,5}/', '/\s{2,}/');
			$replace = array('', '[br]', '[tab]', '[tab]', ' ');

			$txt = preg_replace($search, $replace, $txt);
			return security::encode($txt, false);
		}
		else
		{
			// WARNING WIKI is assumed NOT to require
			// escaped \'s, so we REMOVE them if they were added by the magic_quotes_gpc
			$search = array('/&/', '/</', '/>/', '/\'/', '/"/');
			$replace = array('&amp;', '&lt;', '&gt;', '&#039;', '&quot;');
			if( get_magic_quotes_gpc() )
				$txt = stripslashes($txt);
			return preg_replace($search, $replace, trim($txt));
		}
	}
}

?>
