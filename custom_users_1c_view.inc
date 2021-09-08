<?php

/**
 * @file
 * View Users.
 */

/**
 * View list users 1c.
 */
function custom_users_1c_view() {
  $output = "";
  $params = array();
  $users_list = entity_get_controller(Users1cController::ENTITY_TYPE)->loadList($params);
  $user_empty = (array) entity_get_controller(Users1cController::ENTITY_TYPE)->create();
  unset($user_empty['type']);
  $headers = array_keys($user_empty);
  $table_rows = array();
  foreach ($users_list as $user) {
    $row = array();
    foreach ($headers as $val) {
      $row[$val] = $user->{$val};
    }
    $table_rows[] = $row;
  }
  $output = (theme('table', array('header' => $headers, 'rows' => $table_rows)));
  return $output;
}
