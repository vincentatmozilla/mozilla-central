/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

function run_test() {
  setupTestCommon(true);

  logTestInfo("testing that the update.log is moved after a successful update");

  writeUpdatesToXMLFile(getLocalUpdatesXMLString(""), false);
  var patches = getLocalPatchString(null, null, null, null, null, null,
                                    STATE_PENDING);
  var updates = getLocalUpdateString(patches);
  writeUpdatesToXMLFile(getLocalUpdatesXMLString(updates), true);
  writeStatusFile(STATE_SUCCEEDED);

  var dir = getUpdatesDir();
  var log = dir.clone();
  log.append("0");
  log.append(FILE_UPDATE_LOG);
  writeFile(log, "Last Update Log");

  standardInit();

  logTestInfo("testing " + log.path + " shouldn't exist");
  do_check_false(log.exists());

  log = dir.clone();
  log.append(FILE_LAST_LOG);
  logTestInfo("testing " + log.path + " should exist");
  do_check_true(log.exists());

  logTestInfo("testing " + log.path + " contents");
  do_check_eq(readFile(log), "Last Update Log");

  log = dir.clone();
  log.append(FILE_BACKUP_LOG);
  logTestInfo("testing " + log.path + " shouldn't exist");
  do_check_false(log.exists());

  dir.append("0");
  logTestInfo("testing " + dir.path + " should exist (bug 512994)");
  do_check_true(dir.exists());

  do_test_finished();
}

function end_test() {
  cleanupTestCommon();
}
