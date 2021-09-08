<?php

/**
 * @file
 * Data users_1c controller entity.
 */

/**
 * Interface Users1cInterface for users_1c.
 */
interface Users1cInterface extends DrupalEntityControllerInterface {
  public function create();
  public function save($entity);

}

/**
 * Controller Users1cController for users_1c.
 */
class Users1cController extends DrupalDefaultEntityController implements Users1cInterface {

  const ENTITY_TYPE = 'users_1c';
  const ENTITY_KEY_ID = 'user_id';

  /**
   * Create entity users_1c.
   */
  public function create() {
    $entity = new stdClass();
    $entity->type = self::ENTITY_TYPE;
    $entity->user_id = 0;
    $entity->id_contr = '';
    $entity->description_full = '';
    $entity->description = '';
    $entity->edrpou = '';
    $entity->main_manager = '';
    $entity->code = 0;
    $entity->inn = 0;
    $entity->main_contact = '';
    return $entity;
  }

  /**
   * Load entity users_1c by id primary key.
   */
  public function loadByUserId($id) {
    $entity = $this->entity_load_multiple(array(
      $id,
    ), array());
    return reset($entity);
  }

  /**
   * Load entity users_1c by id_contr.
   */
  public function entityLoadByIdContr($id_contr) {
    $conditions = array(
      'id_contr' => $id_contr,
    );
    $r = $this->entityLoadMultiple(array(), $conditions);
    return reset($r);
  }

  /**
   * Multiple load entities users_1c by conditions.
   */
  public function entityLoadMultiple($ids = array(), $conditions = array()) {
    return entity_load(self::ENTITY_TYPE, $ids, $conditions);
  }

  /**
   * Save entity users_1c.
   */
  public function save($entity) {
    if (empty($entity->user_id)) {
      module_invoke_all('entity_presave', $entity, self::ENTITY_TYPE);
      $primary_keys = $entity->user_id ? self::ENTITY_KEY_ID : array();
      drupal_write_record(self::ENTITY_TYPE, $entity, $primary_keys);
      module_invoke_all('entity_insert', $entity, self::ENTITY_TYPE);
    }
    else {
      module_invoke_all('entity_presave', $entity, self::ENTITY_TYPE);
      $primary_keys = $entity->user_id ? self::ENTITY_KEY_ID : array();
      drupal_write_record(self::ENTITY_TYPE, $entity, $primary_keys);
      module_invoke_all('entity_update', $entity, self::ENTITY_TYPE);

    }

    entity_get_controller(self::ENTITY_TYPE)->resetCache(array($entity->user_id));
    return $entity;
  }

  /**
   * Delete entity users_1c.
   */
  public function entityDelete($id) {
    $id = (int) $id;
    db_delete(self::ENTITY_TYPE)
      ->condition(self::ENTITY_KEY_ID, $id, '=')
      ->execute();
  }

  /**
   * Load list entity users_1c.
   */
  public function loadList($params = array()) {
    $params['count'] = (!empty($params['count'])) ? ($params['count']) : 0;
    $params['limit'] = (!empty($params['limit'])) ? ((int) $params['limit']) : 10;
    $params['offset'] = (!empty($params['offset'])) ? ((int) $params['offset']) : 0;
    if (isset($params['op'])) {
      if ($params['op'] == 'next') {
        $params['offset'] = $params['offset'] + 1;
      }
      if ($params['op'] == 'previous' && (($params['offset'] - 1) > 0)) {
        $params['offset'] = $params['offset'] - 1;
      }
    }

    $sql = db_select(self::ENTITY_TYPE, 'usic')->fields('usic');

    if (isset($params['edrpou'])) {
      $sql->condition('usic.edrpou', $params['edrpou'], '=');
    }
    if (isset($params['main_contact'])) {
      $sql->condition('usic.main_contact', $params['main_contact'], '=');
    }
    if (!empty($params['user_id_order_asc'])) {
      $sql->orderBy('usic.user_id', 'ASC')->range($params['offset'], $params['limit']);
    }
    else {
      $sql->orderBy('usic.user_id', 'DESC')->range($params['offset'], $params['limit']);
    }

    if (!empty($params['count'])) {
      $result = $sql->countQuery()->execute()->fetchField();
    }
    else {
      $result = $sql->execute()->fetchAll();
    }
    return $result;
  }

}
