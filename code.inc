<?php

class code
{
	public $name;
	public $language;
	private $declaration;
	private $push;
	private $pull;
	private $other;

	
	public function __construct($name, $language)
	{
		$this->name = $name;
		$this->language = $language;
	}
	
	public function generate($declaration, $push, $pull, $other)
	{
		$this->declaration = $declaration;
		$this->push = $push;
		$this->pull = $pull;
		$this->other = $other;
		
		switch( $this->language )
		{
			case '1': 
				$code = $this->genPHP();
			break;
			case '2':
				$code = $this->genJava();
			break;
		}
		
		return $code;
	}
	
	private function genPHP()
	{
		$code  = "
class {$this->name} extends Object
{
{$this->declaration}
	
	public function __construct()
	{
	}
	
	public function push(\$message, \$input)
	{
{$this->push}
	}
	
	public function pull(\$output)
	{
{$this->pull}
	}
	
{$this->other}
}";	
		return $code;
	}
}

?>
