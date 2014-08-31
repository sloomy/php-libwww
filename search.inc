<?php

class search
{
	private $data = array();
	private $titles = array();
	private $path = array();
	
	public function __construct($directory)
	{
		if( is_array($directory) )
		{
			foreach( $directory as $d )
			{
				if( $handle = opendir($d) )
				{
					while( false !== ($file = readdir($handle)) )
					{
						if( $file != "." && $file != ".." && strtolower(substr($file, strrpos($file, '.') + 1)) == 'lang' )
						{
							$page = explode('.', $file);
							$page = $page[0];
							
							$new_data = parse_ini_file($d . '/' . $file, true );
							if( is_array($new_data[$GLOBALS['CONFIG']['LANGUAGE']]) )
							{
								foreach( $new_data[$GLOBALS['CONFIG']['LANGUAGE']] as $key => $value )
								{
									$this->data[$page] .= $value;
								}
								
								$this->titles[$page] = $new_data[$GLOBALS['CONFIG']['LANGUAGE']]['title'];
								$this->path[$page] = $d;
							}					
						}
					}
				}
				closedir($handle);				
			}
		}
		else
		{
			if( $handle = opendir($directory) )
			{
				while( false !== ($file = readdir($handle)) )
				{
					if( $file != "." && $file != ".." && strtolower(substr($file, strrpos($file, '.') + 1)) == 'lang' )
					{
						$page = explode('.', $file);
						$page = $page[0];
						
						$new_data = parse_ini_file($directory . '/' . $file, true );
						if( is_array($new_data[$GLOBALS['CONFIG']['LANGUAGE']]) )
						{
							foreach( $new_data[$GLOBALS['CONFIG']['LANGUAGE']] as $key => $value )
							{
								$this->data[$page] .= $value;
							}
							
							$this->titles[$page] = $new_data[$GLOBALS['CONFIG']['LANGUAGE']]['title'];
							$this->path[$page] = $directory;
						}					
					}
				}
			}
			closedir($handle);
		}
		
		
	}
	
	public function find($keyword)
	{		
		$output = array();
		$results = preg_grep("/{$keyword}/", $this->data);

		foreach( $results as $key => $value )
		{
			$start = strpos($value, $keyword)-50;
			$lenght = strlen($keyword)+100;
			
			$output[$key]['content'] = '[...]' . strip_tags(substr($value, $start, $lenght)) . '[...]';
			$output[$key]['content'] = str_ireplace($keyword, "<span style='background-color: #f1c69c;'>{$keyword}</span>", $output[$key]['content']);
			$output[$key]['title'] = $this->titles[$key];
		}
		
		return $output;
	}
	
	public function getPath($page)
	{
		return $this->path[$page];
	}
}

?>
