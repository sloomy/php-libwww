<?php

class resizer
{
	const JPG = 0;
	const GIF = 1;
	const PNG = 2;
	const UNKNOWN = 3;
	
	private $final = null;
	private $format;
	
	public function __construct($filename, $width = 100, $height = 100)
	{
		$this->format = $this->detectFormat($filename);
		
		if( $this->format == self::GIF )
			$src_img = imagecreatefromgif($filename);
		else if( $this->format == self::JPG )
			$src_img = imagecreatefromjpeg($filename);
		else if( $this->format == self::PNG )
			$src_img = imagecreatefrompng($filename);
		else
			return;
		
		$iw = imageSX($src_img);
		$ih = imageSY($src_img);
		if ($iw > $ih )
		{
			$thumb_w = $width;
			$thumb_h = $ih *($height/$iw);
		}
		if ($iw < $ih )
		{
			$thumb_w = $iw*($width/$ih );
			$thumb_h = $height;
		}
		if ($iw == $ih )
		{
			if( $iw > $width )
				$thumb_w = $width;
			else
				$thumb_w = $iw;
			if( $ih > $height )
				$thumb_h = $height;
			else
				$thumb_h = $ih;
		}
		
		$this->final = imagecreatetruecolor($thumb_w, $thumb_h);
		
		if( !imagecopyresampled($this->final, $src_img, 0, 0, 0, 0, $thumb_w, $thumb_h, $iw, $ih) )
		{
			imagedestroy($this->final);
			$this->final == null;
		}
		
		imagedestroy($src_img);
	}
	
	private function detectFormat($filename)
	{
		if( !file_exists($filename) )
			return self::UNKNOWN;

		$image = file_get_contents($filename);
		if( preg_match('/^\x89\x50\x4E\x47\x0D\x0A\x1A\x0A/', $image) )
			return self::PNG;
		if( preg_match('/^\x47\x49\x46\x38(\x39|\x37)\x61/', $image) )
			return self::GIF;
		if( preg_match('/^\xFF\xD8/', $image) )
			return self::JPG;
		return self::UNKNOWN;
	}
	
	public function __destruct()
	{
		imagedestroy($this->final);
	}
	
	public function save($path, $filename, $format = null)
	{
		if( file_exists($path.$filename) )
			unlink($path.$filename);
		
		if( $format != null )
			$this->format = $format;

		switch($this->format)
		{
			case GIF:
				return ( $this->final != null && imagegif($this->final, $path.$filename) && chmod($path.$filename, 0644) );
			case JPG:
				return ( $this->final != null && imagejpeg($this->final, $path.$filename) && chmod($path.$filename, 0644) );
			default:
			case PNG:
				return ( $this->final != null && imagepng($this->final, $path.$filename) && chmod($path.$filename, 0644) );
		}
	}
}

?>
