/* global window */

function oasResults(tmpdir) {
    document.getElementById('tmpdir').value = tmpdir;
//    document.getElementById('list').value = tmpdir+'/results.lst';
//    document.getElementById('uimode').value = 'mini';
//    document.getElementById('p3form').submit();
    oasPopupWindow = window.open('/pager?as='+tmpdir,'oasresults',
 "dependent,height="+600+","
 +"width="+800+","
 +"screenX="+'300'+","
 +"screenY="+'0'+","
 +"resizable,scrollbars,toolbar");
    if (oasPopupWindow) {
	oasPopupWindow.focus();
    } else {
	alert('Oracc Advanced Search requires popups to be enabled for the Oracc server you are using');
    }
}
