<?php

/**
 * @file
 * Form User.
 */

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
 * Form User submit.
 */
function custom_users_1c_form_submit($form, &$form_state) {

}
