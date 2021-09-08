<?php

/**
 * @file
 * Form User 1c. TO DO validate data_user from  custom_users_1c_form_save_data.
 */

define("CUSTOM_USERS_1C_URL_POST_EXTERNAL", "https://erp.climasoft.com.ua/core/hs/ExchangeSite/GetContrData");
define("CUSTOM_USERS_1C_URL_POST_EXTERNAL_LOGIN", "Bot");
define("CUSTOM_USERS_1C_URL_POST_EXTERNAL_PASSWORD", "nl5pusyk");

/**
 * Form User.
 */
function custom_users_1c_form($form, &$form_state) {
  $form['user_id'] = array(
    '#type' => 'textfield',
    '#title' => t('User id'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  return $form;
}

/**
 * Form User 1c validate.
 */
function custom_users_1c_form_validate($form, &$form_state) {
  if (empty($form_state['input']['user_id'])) {
    form_set_error("user_id", t("Empty string"));
  }
  if (!empty($form_state['input']['user_id']) && !preg_match("/^[aA-zZ0-9]+$/u", $form_state['input']['user_id'])) {
    form_set_error("user_id", t("Bad string"));
  }

  return $form;
}

/**
 * Form User 1c submit.
 */
function custom_users_1c_form_submit($form, &$form_state) {
  $url = variable_get("user_1c_url", CUSTOM_USERS_1C_URL_POST_EXTERNAL);
  $login = variable_get("user_1c_login", CUSTOM_USERS_1C_URL_POST_EXTERNAL_LOGIN);
  $pass = variable_get("user_1c_pass", CUSTOM_USERS_1C_URL_POST_EXTERNAL_PASSWORD);

  $options = array(
    'headers' => array(
      'Content-Type' => 'application/json',
      'Authorization' => 'Basic ' . base64_encode($login . ':' . $pass),
    ),
    'data' => drupal_http_build_query(array(
      'IDContr' => $form_state['input']['user_id'],
    )),
    'method' => 'POST',
  );
  $result = drupal_http_request($url, $options);

  if (!($result->status_message == 'OK' && $result->code == 200)) {
    form_set_error("user_id", t("impossible to pull data user"));
    return $form;
  }

  $data_user = drupal_json_decode($result->data);
  $id_contr = $form_state['input']['user_id'];
  custom_users_1c_form_save_data($data_user, $id_contr);
  return $form;
}

/**
 * Form User 1c save data.
 */
function custom_users_1c_form_save_data($data_user, $id_contr) {
  $user = entity_get_controller(Users1cController::ENTITY_TYPE)->entityLoadByIdContr($id_contr);
  if (!$user) {
    $user = entity_get_controller(Users1cController::ENTITY_TYPE)->create();
  }
  $user->id_contr = $id_contr;
  $user->description_full = $data_user['DescriptionFull'];
  $user->description = $data_user['Description'];
  $user->edrpou = $data_user['EDRPOU'];
  $user->main_manager = $data_user['MainManager'];
  $user->code = $data_user['Code'];
  $user->inn = $data_user['INN'];
  $user->main_contact = $data_user['MainContact'];
  entity_get_controller(Users1cController::ENTITY_TYPE)->save($user);
  drupal_set_message(t('User @id_contr saved', array('@id_contr' => $id_contr)), 'status');
}
