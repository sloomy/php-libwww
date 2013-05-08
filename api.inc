<?php

class api
{
	public static function send($action='', $params=array(), $auth=null, $file=false)
	{
		$boundary = "trlalaaaaaaaaaaaaaaaaalalalaalalaaaaaaaaaaa";
		
		if( !isset($params['auth']) && $auth == null )
			$params['auth'] = security::get('API_AUTH');//$GLOBALS['CONFIG']['API_USERNAME'].':'.$GLOBALS['CONFIG']['API_TOKEN'];
		else if( $auth != null )
			$params['auth'] = $auth;
		if( !isset($params['output']) )
			$params['output'] = 'json';
		
		$params['nohttperrorheader'] = true;

		$request = array( 'http' => array( 'user_agent' => 'PHP/5.x (Olympe) API/1.0', 'method' => 'POST', 'timeout' => 10.0 ));

		if( is_array($file) )
			$request['http']['content'] = self::buildMultipartQuery($params, $file);
		else
			$request['http']['content'] = http_build_query(array('json'=>json_encode($params)));
			
		$request['http']['header']  = 'Content-Length: ' . strlen($request['http']['content']) . "\r\n";
		
		if( is_array($file) )
			$request['http']['header'] .= 'Content-Type: multipart/form-data, boundary=' . $boundary . "\r\n";
		else
			$request['http']['header'] .= 'Content-Type: application/x-www-form-urlencoded' . "\r\n";

		try
		{
			$fh = fopen($GLOBALS['CONFIG']['API_HOST'].'/'.$action, 'r', false, stream_context_create( $request ));
			if( $fh === false )
				throw new SiteException("Internal communication error", 500, "No answer from /{$action}");

			$response = stream_get_contents($fh);
			fclose($fh);
			$response = json_decode($response, true);
			if( isset($response['error']) )
				throw new SiteException("Api error", 500, "Error code {$response['error']['code']} for /{$action}", $response['error']['message'] . ' - ' . $response['error']['debug']);
			if( !isset($response['response']) )
				throw new SiteException("Api error", 500, "Unexpected response to /{$action}", print_r($response, true));
			return $response['response'];
		}
		catch(Exception $e)
		{
			// get the E_WARNING from the fopen
			$ex = preg_replace("/fopen\\((.*?)\\)/", "fopen(-http stream-)", $e.'');
			throw new SiteException("Internal communication error", 500, "Upstream API failure", $ex);
		}
	}
	
	public static function buildMultipartQuery($params, $file)
	{
		$boundary = "trlalaaaaaaaaaaaaaaaaalalalaalalaaaaaaaaaaa";
		$content = '--' . $boundary . "\n";
		
		foreach( $params as $key => $value )
			$content .= 'content-disposition: form-data; name="' . $key . '"' . "\n\n" . $value . "\n" . '--' . $boundary . "\n";
		
		$content .= 'content-disposition: form-data; name="file"; filename="' . $file['name'] . '"' . "\n";
		$content .= 'Content-Type: ' . $file['type'] . "\n";
		$content .= 'Content-Transfer-Encoding: binary' . "\n\n";
		$content .= $file['binary'];
		$content .= "\n" . '--' . $boundary . "\n";

		return $content;
	}
}

?>
