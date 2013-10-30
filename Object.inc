<?php

abstract class Object
{
	public $name = "undefined";
	protected $outputs = array();
	protected $inputs = array();
	protected $config = array();
	
	public abstract function push($message, $input);
	public abstract function pull($output);
	
	private $configured = false;
	public function configure($config)
	{
		if( $this->configured )
			throw new Exception("Object is already configured");
		$this->configured = true;
		
		if( is_array($config) )
		{
			foreach( $config as $c )
			{
				$key = $c['name'];
				$value = $c['value'];
				
				$this->config[$key] = $value;
			}
		}
	}
	
	private $inputsSet = false;
	public function setInputs($in)
	{
		if( $this->inputsSet )
			throw new Exception("Object inputs are already set");
		$this->inputsSet = true;
		
		if( is_array($in) )
		{
			foreach( $in as $i )
				$this->inputs[] = array('index'=>$i['index'], 'name'=>$i['name'], 'value'=>$i['value']);
		}
	}
	
	private $outputsSet = false;
	public function setOutputs($out)
	{
		if( $this->outputsSet )
			throw new Exception("Object outputs are already set");
		$this->outputsSet = true;
		
		if( is_array($out) )
		{
			foreach( $out as $o )
				$this->outputs[] = array('index'=>$o['index'], 'name'=>$o['name'], 'value'=>$o['value']);
		}
	}
	
	public function outputCount() { if( is_array($this->outputs) ) return count($this->outputs); else return 0; }
	public function inputCount() { if( is_array($this->inputs) ) return count($this->inputs); else return 0; }
}

?>