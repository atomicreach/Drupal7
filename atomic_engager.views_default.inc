<?php

function atomic_engager_views_default_views() {
    // Begin copy and paste of output from the Export tab of a view.
    $view = new view;
    $view->name = 'arfeed';
    $view->description = 'Generate RSS with 300 full content';
    $view->tag = 'default';
    $view->base_table = 'node';
    $view->human_name = 'AR Feed';
    $view->core = 0;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['title'] = 'AR Feed';
    $handler->display->display_options['use_more_always'] = FALSE;
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'full';
    $handler->display->display_options['pager']['options']['items_per_page'] = '300';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'node';
    $handler->display->display_options['row_options']['view_mode'] = 'full';
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['label'] = '';
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
    /* Sort criterion: Content: Post date */
    $handler->display->display_options['sorts']['created']['id'] = 'created';
    $handler->display->display_options['sorts']['created']['table'] = 'node';
    $handler->display->display_options['sorts']['created']['field'] = 'created';
    $handler->display->display_options['sorts']['created']['order'] = 'DESC';
    /* Filter criterion: Content: Published */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'node';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['group'] = 1;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

    /* Display: Page */
    //$handler = $view->new_display('page', 'Page', 'page');
    //$handler->display->display_options['path'] = 'rss';

    /* Display: Feed */
    $handler = $view->new_display('feed', 'Feed', 'feed');
    $handler->display->display_options['pager']['type'] = 'some';
    $handler->display->display_options['style_plugin'] = 'rss';
    $handler->display->display_options['row_plugin'] = 'node_rss';
    $handler->display->display_options['row_options']['item_length'] = 'rss';
    $handler->display->display_options['row_options']['links'] = TRUE;
    $handler->display->display_options['path'] = 'arfeed.xml';
    $handler->display->display_options['displays'] = array(
        'default' => 'default',
        'page' => 'page',
    );

    $handler->display->display_options['sitename_title'] = '1';

    // (Export ends here.)
    // Add view to list of views to provide.
    $views[$view->name] = $view;

    // At the end, return array of default views.
    return $views;
}
