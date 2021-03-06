<?php

$GLOBALS['CONFIG']['DEBUG'] 		= true;
$GLOBALS['CONFIG']['THROW_ERRORS'] 	= (E_ALL | E_STRICT) & ~E_NOTICE;

$domain = explode( '.', $_SERVER["HTTP_HOST"] );
$file = '/dns/' . array_pop( $domain ) . '/' . array_pop( $domain ) . '/etc/settings' . '/' . implode( '.', $domain ) . '.ini';
if( file_exists( $file ) )
{
    $conf = parse_ini_file( $file, true );
    $conf['type'] = 'file';
}
else if( file_exists( '../www.ini' ) )
{
    $conf = parse_ini_file('../www.ini');
    $conf['type'] = 'file';
}

$GLOBALS['CONFIG']['API_HOST'] 		= 'https://' . $conf['Main']['API_HOST'];
$GLOBALS['CONFIG']['API_USERNAME']	= $conf['Main']['API_USERNAME'];
$GLOBALS['CONFIG']['API_PASSWORD']	= $conf['Main']['API_TOKEN'];
$GLOBALS['CONFIG']['HOSTNAME']		= $conf['Main']['HOSTNAME'];
$GLOBALS['CONFIG']['UPTIME_TOKEN']	= $conf['Main']['UPTIME_TOKEN'];
$GLOBALS['CONFIG']['REDMINE_TOKEN']	= $conf['Main']['REDMINE_TOKEN'];
$GLOBALS['CONFIG']['DEBUG'] 		= false;
unset($conf);
unset($file);

$GLOBALS['CONFIG']['DEFAULT_PAGE']		= '/default';
$GLOBALS['CONFIG']['PANEL_PAGE']		= '/panel';
$GLOBALS['CONFIG']['LOGIN_PAGE']		= '/?elogin';
$GLOBALS['CONFIG']['DEFAULT_LANGUAGE']	= 'FR';

$GLOBALS['CONFIG']['MAIL_TEMPLATE'] = "
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">
<html xmlns=\"http://www.w3.org/1999/xhtml\">
  <head>
    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />
  </head>
  <body style=\"width: 100% !important; -webkit-text-size-adjust: none; margin: 0; padding: 0;\">
    <center>
      <table id=\"backgroundTable\" style=\"border-spacing: 0; border-collapse: collapse; font-family: proxima-nova, 'helvetica neue', helvetica, arial, geneva, sans-serif; height: 100% !important; width: 100% !important; color: #4c4c4c; font-size: 15px; line-height: 150%; background: #ffffff; margin: 0; padding: 0; border: 0;\">
        <tr style=\"vertical-align: top; padding: 0;\">
          <td align=\"center\" valign=\"top\" style=\"vertical-align: top; padding: 0;\">
            <table id=\"templateContainer\" style=\"border-spacing: 0; border-collapse: collapse; font-family: proxima-nova, 'helvetica neue', helvetica, arial, geneva, sans-serif; height: 100%; width: 600px; color: #4c4c4c; font-size: 15px; line-height: 150%; background: #ffffff; margin: 40px 0; padding: 0; border: 0;\">
              <tr style=\"vertical-align: top; padding: 0;\">
                <td class=\"templateContainerPadding\" align=\"center\" valign=\"top\" style=\"vertical-align: top; padding: 0 40px;\">
                  <table id=\"templateContent\" style=\"border-spacing: 0; border-collapse: collapse; font-family: proxima-nova, 'helvetica neue', helvetica, arial, geneva, sans-serif; height: 100%; width: 100%; background: #ffffff; margin: 0; padding: 0; border: 0;\">
                    <tr style=\"vertical-align: top; padding: 0;\">
                      <td style=\"vertical-align: top; text-align: left; padding: 0;\" align=\"left\" valign=\"top\">
                        <h1 id=\"logo\" style=\"color: #de5711; display: block; font-family: hybrea, proxima-nova, 'helvetica neue', helvetica, arial, geneva, sans-serif; font-size: 32px; font-weight: 200; text-align: left; margin: 0 0 40px;\" align=\"left\"><img src=\"https://www.olympe.in/on/images/logo-dark.png\" alt=\"Olympe\" width=\"140\" height=\"42\" style=\"outline: none; text-decoration: none; border: 0;\" /></h1>
						{CONTENT}
					   <p style=\"margin: 20px 0;\">
                          The Olympe Team<br />
                          <a href=\"https://www.olympe.in\" style=\"color: #de5711;\">https://www.olympe.in</a>
                        </p>
                      </td>
                    </tr>
                  </table>
                </td>
              </tr>
              <tr style=\"vertical-align: top; padding: 0;\">
                <td class=\"templateContainerPadding\" align=\"center\" valign=\"top\" style=\"vertical-align: top; padding: 0 40px;\">
                  <table id=\"footerContent\" style=\"border-spacing: 0; border-collapse: collapse; font-family: proxima-nova, 'helvetica neue', helvetica, arial, geneva, sans-serif; height: 100%; width: 100%; border-top-style: solid; border-top-color: #ebeaef; color: #999999; font-size: 12px; background: #ffffff; margin: 0; padding: 0; border-width: 1px 0 0;\">
                    <tr style=\"vertical-align: top; padding: 0;\">
                      <td valign=\"top\" style=\"vertical-align: top; text-align: left; padding: 0;\" align=\"left\">
                        <p style=\"margin: 20px 0;\">
                          Olympe is a free web hosting provider without ads. Our platform supports applications and several databases services.<br />Tools built by the Olympe team are released under Open Source licences.
                        </p>
                        <p style=\"margin: 20px 0;\">
                          To learn more about Olympe and all it's features, check out the documentation: <a href=\"https://www.olympe.in/doc\" style=\"color: #666666;\">https://www.olympe.in/doc</a>
                        </p>
                      </td>
                    </tr>
                  </table>
                </td>
              </tr>
            </table>
          </td>
        </tr>
      </table>
    </center>
<style type=\"text/css\">
body {
width: 100% !important;
}
.ReadMsgBody {
width: 100%;
}
.ExternalClass {
width: 100%;
}
body {
-webkit-text-size-adjust: none;
}
body {
margin: 0; padding: 0;
}
img {
border: 0; outline: none; text-decoration: none;
}
#backgroundTable {
height: 100% !important; margin: 0; padding: 0; width: 100% !important;
}
#backgroundTable {
color: #4c4c4c; background-color: #ffffff; font-family: proxima-nova, 'helvetica neue', helvetica, arial, geneva, sans-serif; font-size: 15px; line-height: 150%;
}
@media (max-width: 540px) {
  #templateContainer {
    width: 100% !important;
  }
  #templateContainer .templateContainerPadding {
    padding: 0 5% !important;
  }
}
</style>
</body>
</html>";

?>
