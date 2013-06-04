<?php

/**
 * @file
 * 
 * Provides ctools context based on node path alias. 
 * 
 * This is assumed from the previous items in the URL from the $arg item supplied
 * 
 *
 * @author Mark Rushton (Modernfidelity Studios)
 * 
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Node: URL Alias"),
  // keyword to use for %substitution
  'keyword' => 'node',
  'description' => t('Creates a context from the node path alias.'),
  'context' => 'node_alias_arg_context',
  // 'settings form' => 'node_alias_plugin_settings_form',
  // placeholder_form is used in panels preview, for example, so we can
  // preview without getting the arg from a URL
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter the node url alias'),
  ),
);


 

/**
 * 
 * Discover if this argument gives us the node, if so return it and create ctools context.
 * 
 */
function node_alias_arg_context($arg = NULL, $conf = NULL, $empty = FALSE) {
  
  // If unset it wants a generic, unfilled context.
  if ($empty) {
    return ctools_context_create_empty('node');
  }

  // We can accept either a node object or a pure nid.
  if (is_object($arg)) {
    return ctools_context_create('node', $arg);
  }
  
  // Get node id from URL alias and load node from nid 
  $node_path = explode($arg, current_path());
 
  // Check if items exist otherwise return false
  if($node_path){
    
    $node_path_alias = $node_path[0] . $arg;
  
    $path = drupal_lookup_path("source", $node_path_alias);

    $node_path_system = explode("/", $path);
     
    // If nid is available load and return node.
    if (isset($node_path_system[1]) && is_numeric($node_path_system[1])) {

      $node = node_load($node_path_system[1]);

    }else {

      return FALSE;

    }
    
  }else{
    
    return FALSE;
    
  }
  
  // Create content for panels + views pages
  return ctools_context_create('node', $node);
  
}


