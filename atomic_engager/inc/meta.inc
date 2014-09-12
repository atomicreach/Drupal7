<?php

/*
 * Display AtomicReach assessment results.
 * Following class takes the Json formatted result and display it in human friendly format.
 * See: ../index.php From Line#90 to call each method.
 * Please take backup before you edit this file.
 * 
 */

class meta {

    private $result;

    // Contructor getting result from ARClient.php in a form of an object.
    Public function __construct($obj) {
        $this->result = $obj;
    }

    /*     * *************************** */
    /* Content Sophistication    */
    /* find out more about this:   */
    /* http://www.slideshare.net/atomicreach/how-to-achieve-a-content-sophistication-match-for-your-audience */
    /*     * *************************** */

    public function contentSophistication() {
        $num = 0;
        $so = $this->result->data->analysis->so;
        $out = '<div class="' . $this->DOMsort($so->state) . '">' . PHP_EOL;
        $out .= '<input id="so" name="so" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="so" id="ar-' . $so->state . '">Content Sophistication</label>' . PHP_EOL;
        $out .= '<article class="ac-large">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $so->state . '">Your content is ' . $so->detail . ' for your audience</p>' . PHP_EOL;
//    $out .= '<ul class="details paragraph-sophistication">' . PHP_EOL;

        if (!empty($so->paragraphs)) {
            if ($so->detail === 'TOO SIMPLE') {
                $ar_message = '<p><strong>TIPS:</strong> consider elaborating on short sentences and/ or use more sophisticated language.</p>';
            } elseif ($so->detail === 'TOO COMPLEX') {
                $ar_message = '<p><strong>TIPS:</strong> Write shorter sentences, use shorter words, break up paragraphs.</p>';
            }
            $ar_message .= '<p><br />Utilize the article highlighting (<strong>Audience Mismatch</strong>) button above to see where you should modify your content to match your audience. <br /> <span style="color: #91c7f9;">Blue highlights = Too simple.</span> <span style="color: #FFA20C;">Orange highlights = Too complex.</span>
                                     <br />
                                    <a href="https://www.slideshare.net/secret/ydYaIIq7pSJDxK" target="_blank" class="toggle-link ar-message-link">Refer to our tips on how to achieve a content sophistication match for your audience <span>here</span></a>.</p>';
            $out .= $ar_message . PHP_EOL;
        }
//    $out .= '</ul>';
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ************************** */
    /*   Underperforming Count    */
    /*     * ************************** */

    public function linkCount() {
        $lc = $this->result->data->analysis->lc;
        $out = '<div class="' . $this->DOMsort($lc->state) . '">' . PHP_EOL;
        $out .= '<input id="lc" name="lc" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="lc" id="ar-' . $lc->state . '">Underperforming Link(s)</label>' . PHP_EOL;
        $out .= '<article class="ac-small">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $lc->state . '">';
        if ($lc->invalid >= 1) {
            if ($lc->invalid == 1) {
                $verb = 'is';
            } else {
                $verb = 'are';
            }
            $out .= $lc->invalid . ' out of the ' . $lc->total . ' links included in the posts ' . $verb . ' underperforming' . PHP_EOL;
            $out .= '<ul class="invalid-links">';
            foreach ($lc->detail AS $links) {
                $out .= '<li><a href="' . $links . '" target="_blank"><span class="ilText">' . $links . '</span></a></li>' . PHP_EOL;
            }
            $out .= '</ul>';
        } else {
            $out .= 'All links are valid';
        }
        $out .= '</p>' . PHP_EOL;
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ******************** */
    /*   Content Length     */
    /*     * ******************** */

    public function contentLength() {
        $ln = $this->result->data->analysis->ln;
        $out = '<div class="' . $this->DOMsort($ln->state) . '">' . PHP_EOL;
        $out .= '<input id="ln" name="ln" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="ln"  id="ar-' . $ln->state . '">Content Length</label>' . PHP_EOL;
        $out .= '<article class="ac-small">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $ln->state . '">';
//    if ($ln->state == 'green') {
        $out .= 'length of post is ' . $ln->measured->sentences . ' sentences. For text based posts our recommended range is ' . $ln->recommended->sentencesMin . '-' . $ln->recommended->sentencesMax . ' sentences for greater engagement.';
//    } else {
//      $out .= 'length of post is ' . $ln->measured->sentences . ' sentences. For text based posts our recommended range is 25-75 sentences for greater engagement.';
//    }
        $out .= '</p>' . PHP_EOL;
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ************************ */
    /*   Content Originality    */
    /*     * ************************ */

    public function contentOriginality() {
        $su = $this->result->data->analysis->su;
        $out = '<div class="' . $this->DOMsort($su->state) . '">' . PHP_EOL;
        $out .= '<input id="su" name="su" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="su" id="content-orginality">Content Originality</label>' . PHP_EOL;
        $out .= '<article class="ac-small">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $su->state . '">';
        if ($su->state == 'green') {
            $msg = '<img class="ar-thumbsUp" src="' . $base_url . '/sites/all/modules/atomicreach/images/thumbs_up.png">Your content is unique and will drive engagement, so share away!';
        } else {
            $msg = 'Original content drives more engagement. We will alert you when your content is unique.';
        }
        $out .= $msg;
        $out .= '</p>' . PHP_EOL;
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ************************ */
    /*     Content Emotion      */
    /*     * ************************ */

    public function contentEmotion() {
        $em = $this->result->data->analysis->em;
        if ($em->state == 'red') {
            $colour = 'yellow';
        } else {
            $colour = $em->state;
        }
        $out = '<div class="' . $this->DOMsort($colour) . '">' . PHP_EOL;
        $out .= '<input id="em" name="em" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="em"  id="ar-' . $colour . '">Content Emotion</label>' . PHP_EOL;
        $out .= '<article class="ac-large">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $colour . '">';
//    $out .= $em->detail;
        $out .= '<ul class="emotion-details">';
        foreach ($em->dimensions as $key => $value) {
            $out .= '<li class="emotion-' . strtolower($value->state) . '"><strong>' . $value->name . '</strong>: ' . $value->detail . '</li>';
        }
        $out .= '</ul>';


        $out .= '</p>' . PHP_EOL;
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ************************ */
    /*   Spelling Mistakes      */
    /*     * ************************ */

    public function spellingMistakes() {
        $sm = $this->result->data->analysis->sm;
        $out = '<div class="' . $this->DOMsort($sm->state) . '">' . PHP_EOL;
        $out .= '<input id="sm" name="sm" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="sm"  id="ar-' . $sm->state . '">Spelling Mistakes</label>' . PHP_EOL;
        $out .= '<article class="ac-large">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $sm->state . '">There ';
        $out .= ($sm->total == 1) ? 'is ' : 'are ';
        $out .= $sm->total . ' misspelled word(s).</p>' . PHP_EOL;
        if (is_array($sm->detail)) {
            $out .= '<ul class="spelling-mistakes">';
            foreach ($sm->detail as $value) {
                $out .= '<li><span class="smText">' . $value->string . '</span><strong> Suggestions: </strong>';
                //if($result->data->analysis->sm->total > 0) {
                if (!empty($value->suggestions->option)) {
                    if (!is_array($value->suggestions->option)) {
                        $value->suggestions->option = array(
                            $value->suggestions->option
                        );
                    }
                    $suggestions = array();
                    foreach ($value->suggestions->option AS $v) {
                        array_push($suggestions, $v);
                    }
                    $out .= implode(", ", $suggestions);
                }
                //  }
                $out .= '</li>' . PHP_EOL;
            }
            $out .= '</ul>';
        } // end if is array.
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ************************ */
    /*    Grammar Mistakes      */
    /*     * ************************ */

    public function grammarMistakes() {
        $gm = $this->result->data->analysis->gm;
        $out = '<div class="' . $this->DOMsort($gm->state) . '">' . PHP_EOL;
        $out .= '<input id="gm" name="gm" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="gm" id="ar-' . $gm->state . '">Grammar Insights</label>' . PHP_EOL;
        $out .= '<article class="ac-large">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $gm->state . '">There ';
        $out .= ($gm->total == 1) ? 'is ' : 'are ';
        $out .= $gm->total . ' grammar error(s).</p>' . PHP_EOL;
        if (is_array($gm->detail)) {
            $out .= '<ul class="grammar-mistakes">';
            foreach ($gm->detail as $value) {
                if (!empty($value->suggestions)) {
                    if (!is_array($value->suggestions)) {
                        $value->suggestions = array(
                            $value->suggestions
                        );
                    }
                }
                $out .= '<li><span class="gmText">' . $value->string . '</span> - <a href="' . $value->url . '" target="_blank">See Explanation</a></li>' . PHP_EOL;
            }
            $out .= '</ul>';
        } // end if is array.
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ****************** */
    /*    Topics Tags     */
    /*     * ****************** */

    public function topicsTags() {
        $tg = $this->result->data->analysis->tg;
        $out = '<div class="' . $this->DOMsort($tg->state) . '">' . PHP_EOL;
        $out .= '<input id="tg" name="accordion-1" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="tg" id="ar-' . $tg->state . '">' . $tg->total . ' Keyword(s)</label>' . PHP_EOL;
        $out .= '<article class="ac-large">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $tg->state . '">';
        if ($tg->total >= 1) {
            $out .= $tg->total . ' Keyword(s) identified. ' . PHP_EOL;
            $out .= '<ul>';
            foreach ($tg->detail AS $tags) {
                $out .= '<li>' . $tags . '</li>' . PHP_EOL;
            }
            $out .= '</ul>';
        } else {
            $out .= '0 tags identified.';
        }
        $out .= '</p>' . PHP_EOL;
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ************************ */
    /*   Content Clarity    */
    /*     * ************************ */

    public function contentClarity() {
        $lr = $this->result->data->analysis->lr;
        $out = '<div class="' . $this->DOMsort($lr->state) . '">' . PHP_EOL;
        $out .= '<input id="lr" name="lr" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="lr"  id="ar-' . $lr->state . '">Content Clarity</label>' . PHP_EOL;
        $out .= '<article class="ac-small">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $lr->state . '">';
        $out .= $lr->detail;
        $out .= '</p>' . PHP_EOL;
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * *********************** */
    /*   Title Optimization   */
    /*     * *********************** */

    public function titleOptimization() {
        $tm = $this->result->data->analysis->tm;
        $out = '<div class="' . $this->DOMsort($tm->state) . '">' . PHP_EOL;
        $out .= '<input id="tm" name="tm" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="tm"  id="ar-' . $tm->state . '">Title Optimization</label>' . PHP_EOL;
        $out .= '<article class="ac-large">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $tm->state . '">';
        $out .= "<strong>" . $tm->message . "</strong>";
        $out .= '</p>' . PHP_EOL;
        if ($tm->detail >= 0) {
            $num = 1;
            $out .= "<ul class='tm'>";
            foreach ($tm->recomendations AS $rec) {
                if (!empty($rec)) {
                    $out .= "<li>" . $rec . "</li>";
                    $num++;
                }
            }
            $out .= "</ul>";
        }
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    public function displayHighlightsButtons() {
        if ($this->result->data->analysis->sm->total > 0 || $this->result->data->analysis->gm->total > 0 || $this->result->data->analysis->lc->invalid > 0 || strtolower($this->result->data->analysis->so->state !== 'green')):
            $out = '';
            $out .= '<strong>Select a category to highlight areas to refine:</strong>';
            $out .= '<ul id="hl-class">';
            if ($this->result->data->analysis->sm->total > 0):
                $out .= '<li>';
                $out .= '<input type="checkbox" id="chksp" name="chk" value="all">
<label for="chksp">Spelling Mistakes</label>
</li>';
            endif;
            if ($this->result->data->analysis->gm->total > 0):
                $out .= '<li>   
<input type="checkbox" id="chkgm" name="chk"value="false">
<label for="chkgm">Grammar Mistakes</label>
</li>';
            endif;
            if ($this->result->data->analysis->lc->invalid > 0):
                $out .= '<li>   
<input type="checkbox" id="chkul" name="chk" value="true">
<label for="chkul">Underperforming Links</label>
</li>';
            endif;
            if (strtolower($this->result->data->analysis->so->state !== 'green')):
                $out .= '<li>   
<input type="checkbox" id="chkso" name="chk"value="false">
<label for="chkso">Audience Mismatch</label>
</li>';
                $light_blue = '#91c7f9';
                $light_orange = '#FFA20C';
                $out .= '<script type="text/javascript">
                         var tooSimpleColor = ' . drupal_json_encode($light_blue) . ';
                         var tooComplexColor = ' . drupal_json_encode($light_orange) . ';
                         var domExpression = ' . drupal_json_encode($this->result->data->analysis->so->paragraphDOM) . ';
                         var paragraphs = ' . drupal_json_encode($this->result->data->analysis->so->paragraphs) . ';
                         </script>';
            endif;
            $out .= '</ul>   ';
            return $out;
        endif;
    }

    public function displayScore() {
        $score = $this->result->data->scoring;
        if ($score <= 50) {
            $msg = '<span style="color: #F72210;">Need Changes!</span>';
        } elseif ($score > 50 && $score < 75) {
            $msg = '<span style="color:  #F6D610;">Almost There!</span>';
        } elseif ($score >= 75) {
            $msg = '<span style="color:  #2ecc71;">On Your Way!</span>';
        }


//    $out  = '<div class="ar-score-wrapper">';
//    $out .= '</div>';
        $out = '<div class="ar-score-container"><span>' . $score . '</span></div>';
        $out .= '<p class="ar-msg">Aim for an Atomic Score of 60+, but with the suggestions below you can gain even greater engagement.</p>';
        $out .= '<div class="ar-progress">';
        $out .= '<div class="ar-bar bar-danger" style="width: 50%;"></div>';
        $out .= '<div class="ar-bar bar-warning" style="width: 30%;"></div>';
        $out .= '<div class="ar-bar bar-success" style="width: 20%;"></div>';
        $out .= '<div class="ar-score" style="left:' . $score . '%;"><i class="fa fa-long-arrow-up"></i></div>';
        $out .= '</div>';
        $out .= '<div class="ar-score-message">' . $msg . '</div>';
        return $out;
    }

    public function displayResult() {
        return $this->result;
    }

    public function DOMsort($state) {
        if (strtolower($state) == "green") {
            return "3";
        } else if (strtolower($state) == "yellow") {
            return "2";
        } else if (strtolower($state) == "red") {
            return "1";
        }
    }

    public function atomicScore() {
        return $this->result->data->scoring;
    }

}

?>