<?php

/*
    Copyright (C) 2014-2015 Deciso B.V.
    Copyright (C) 2012 Seth Mos
    Copyright (C) 2004-2009 Scott Ullrich
    Copyright (C) 2003-2004 Manuel Kasper <mk@neon1.net>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
    AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
    OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

require_once("guiconfig.inc");
require_once("system.inc");
require_once("interfaces.inc");

/* expects $logfile to point to the system path */
/* expects $logclog to be true or false */

$filtertext = '';
$nentries = 50;

if (isset($config['syslog']['nentries'])) {
    $nentries = $config['syslog']['nentries'];
}

if (!empty($_POST['clear'])) {
    if ($logclog) {
        clear_clog($logfile);
    } else {
        clear_log($logfile);
    }
}

if (isset($_POST['filtertext'])) {
    $filtertext = htmlspecialchars($_POST['filtertext']);
}

include("head.inc");

?>

<body>
<?php include("fbegin.inc"); ?>
  <section class="page-content-main">
    <div class="container-fluid">
      <div class="row">
        <section class="col-xs-12">
          <div class="tab-content content-box col-xs-12">
            <div class="table-responsive">
              <table class="table table-striped table-sort">
                <tr>
                  <td colspan="2">
                    <form id="clearform" name="clearform" action="<? $_SERVER['REQUEST_URI'] ?>" method="post" class="__mt">
                      <input id="filtertext" name="filtertext" value="<?=$filtertext;?>"/>
                      <input id="filtersubmit" name="filtersubmit" type="submit" class="btn btn-primary" value="<?=gettext("Filter");?>" />
                    </form>
                  </td>
                </tr>
                <?php
                  if ($logclog) {
                      dump_clog($logfile, $nentries, $filtertext);
                  } else {
                      dump_log($logfile, $nentries, $filtertext);
                  }
                ?>
                <tr>
                  <td colspan="2">
                    <form action="<? $_SERVER['REQUEST_URI'] ?>" method="post">
                      <input name="clear" type="submit" class="btn" value="<?= gettext("Clear log");?>" />
                    </form>
                  </td>
                </tr>
              </table>
            </div>
          </div>
        </section>
      </div>
    </div>
  </section>
<?php include("foot.inc"); ?>