<?php

/**
 * @file
 * Form User.
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
  $login = variable_get("user_1c_login", CUSTOM_USERS_1C_URL_POST_EXTERNAL_LOGIN);
  $pass = variable_get("user_1c_pass", CUSTOM_USERS_1C_URL_POST_EXTERNAL_PASSWORD);

  $options = array(
    'headers' => array(
      'Content-Type' => 'application/json',
      'Authorization' => 'Basic ' . base64_encode($login . ':' . $pass),
    ),
    'data' => drupal_http_build_query(array(
      'nid' => $snid,
    )),
    'method' => 'POST',
  );
  $result = drupal_http_request(CUSTOM_USERS_1C_URL_POST_EXTERNAL, $options);

}
