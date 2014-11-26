(function($) {
    Drupal.behaviors.atomic_engager = {
        attach: function(context, settings) {
            $(document).ajaxComplete(function(e, xhr, settings) {

      /********************************/
        /**** Score Button & new-meta.php Tabs ui ****/
        /********************************/
      //  $("#edit-arpost").bind("load", "ul.AR-tabs", ARTabs());
      ARTabs();
        function ARTabs() {
            $('ul.AR-tabs').each(function () {
                // For each set of tabs, we want to keep track of
                // which tab is active and it's associated content
                var $active, $content, $links = $(this).find('a');

                // If the location.hash matches one of the links, use that as the active tab.
                // If no match is found, use the first link as the initial active tab.
                $active = $($links.filter('[href="' + location.hash + '"]')[0] || $links[0]);
                $active.addClass('active');
                $content = $($active[0].hash);

                // Hide the remaining content
                $links.not($active).each(function () {
                    $(this.hash).hide();
                });

                // Bind the click event handler
                // delegatge is supported by jQuery 1.4
                $(this).delegate('a', 'click', function (e) {
                    // Make the old tab inactive.
                    $active.removeClass('active');
                    $content.hide();

                    // Update the variables with the new link and content
                    $active = $(this);
                    $content = $(this.hash);

                    // Make the tab active.
                    $active.addClass('active');
                    $content.show();

                    // Prevent the anchor's default click action
                    e.preventDefault();
                });
            });
        }
    
 



// Spelling Mistakes    
                //aSm = $("ul.spelling-mistakes li").find('span.smText').clone().not(":last").append("\\b|\\b").end().text();
                //var regexSm = new RegExp('(?:\\b|_)(' + aSm + ')(?:\\b|_)', 'ig');
                 var words = $.map(SMwords, function(word, i) { return word.replace(/[\-\[\]\/\{\}\(\)\*\+\?\.\\\^\$\|]/g, "\\$&"); });
          //var regexSm = new RegExp('(\\b[\\W]*'+words.join("[\\W]*\\b|\\b[\\W]*")+'[\\W]*\\b)','ig');
    //          var regexSm = new RegExp('(\\b'+words.join("?[\\x27]?[\\S]+\\b|\\b")+'?[\\x27]?[\\S]+\\b)','ig');
                var regexSm = new RegExp('(\\b' + words.join("([\\x27][\\S]*)?\\b|\\b") + '([\\x27][\\S]*)?\\b)', 'ig');




//
//          console.log("smword: "+SMwords);
//          console.log("regexSM: "+regexSm);

//console.log(regexSm);

                $("#highlight-sp").toggle(function() {
                    $('.form-textarea-wrapper iframe').contents().highlightRegex(regexSm, {
                        tagType: 'span',
                        className: 'highlight-sp'
                    });

                    $('.form-textarea-wrapper iframe').contents().find(".highlight-sp").css("border-bottom", "3px solid #fc0909"); // red
                    $(this).text("Clear Spelling Mistakes");
                }, function() {
                    $('.form-textarea-wrapper iframe').contents().find(".highlight-sp").removeAttr("style")
                    $(this).text('Spelling Mistakes');
                })

                $('#chksp').change(function() {
                   
                    if ($(this).is(":checked")) {
                        $('.form-textarea-wrapper iframe').contents().highlightRegex(regexSm, {
                            tagType: 'span',
                            className: 'highlight-sp'
                        });

                        $('.form-textarea-wrapper iframe').contents().find(".highlight-sp").css("border-bottom", "3px solid #fc0909"); // red

                    } else {

                        $('.form-textarea-wrapper iframe').contents().find(".highlight-sp").removeAttr("style")

                    }
                });

                $('#chkso').change(function() {

                    if ($(this).is(":checked")) {
                        text_paragraphs = $('.form-textarea-wrapper iframe').contents().find(domExpression);
                        $.each(paragraphs, function(index, value) {
                            if (value == 'HIT' || value == 'UNAVAILABLE')
                                return;
                            type = (value == 'TOO SIMPLE') ? 'too-simple' : 'too-complex';
                            $(text_paragraphs[index]).wrapInner("<span class='highlight-so " + type + "'></span>");
                        });
                        $('.form-textarea-wrapper iframe').contents().find(".too-simple").css("background", tooSimpleColor);
                        $('.form-textarea-wrapper iframe').contents().find(".too-complex").css("background", tooComplexColor);

                    } else {
//        console.log("not checked");
                        $('.form-textarea-wrapper iframe').contents().find(".highlight-so").removeAttr("style")

                    }
                });


                // Grammar Mistakes    
//                aGm = $("ul.grammar-mistakes li").find('span.gmText').clone().not(":last").append("|").end().text();
//                var regexGm = new RegExp(aGm, 'g');
            var words = $.map(GMwords, function(word, i) { return word.replace(/[\-\[\]\/\{\}\(\)\*\+\?\.\\\^\$\|]/g, "\\$&"); });          
//            var regexGm = new RegExp('(\\b'+words.join("?[\\x27]?[\\S]+\\b|\\b")+'?[\\x27]?[\\S]+\\b)','g');
                var regexGm = new RegExp('(\\b' + words.join("([\\x27][\\S]*)?\\b|\\b") + '([\\x27][\\S]*)?\\b)', 'g');

                $("#highlight-gm").toggle(function() {
                    $('.form-textarea-wrapper iframe').contents().highlightRegex(regexGm, {
                        tagType: 'span',
                        className: 'highlight-grm',
                    });

                    $('.form-textarea-wrapper iframe').contents().find(".highlight-grm").css("border-bottom", "3px solid #3bd15e"); // green
                    $(this).text("Clear Grammar Mistakes");
                }, function() {

                    $('.form-textarea-wrapper iframe').contents().find(".highlight-grm").removeAttr("style");
                    $(this).text('Grammar Mistakes');
                })



                $('#chkgm').change(function() {

                    if ($(this).is(":checked")) {
                        $('.form-textarea-wrapper iframe').contents().highlightRegex(regexGm, {
                            tagType: 'span',
                            className: 'highlight-grm',
                        });

                        $('.form-textarea-wrapper iframe').contents().find(".highlight-grm").css("border-bottom", "3px solid #3bd15e"); // green

                    } else {
                        $('.form-textarea-wrapper iframe').contents().find(".highlight-grm").removeAttr("style");

                    }
                });

                // Invalid Lunks    
                aIl = $("ul.invalid-links li").find('span.ilText').clone().not(":last").append("|").end().text();

                // aIl = / www.atomicreach.coms | http:\/\/www.atomicreach.comsi\/ewruu /ig

                var linkArray = aIl.split('|');

                /*var regexIl = new RegExp(aIl,'gi');*/

                $("#highlight-il").toggle(function() {

                    /* 
                     $('.form-textarea-wrapper iframe').contents().highlightRegex(regexIl, {
                     tagType:   'span',
                     className: 'highlight-il',
                     });  
                     $('.form-textarea-wrapper iframe').contents().find(".highlight-il").css("border-bottom", "2px solid orange");
                     */


                    $.each(linkArray, function(index, value) {
                        vlink = "[href='" + value + "']";
                        $('.form-textarea-wrapper iframe').contents().find(vlink).css("border-bottom", "3px solid #f7b70c"); // orange
                    });


                    $(this).text("Clear Underperforming Link");
                }, function() {

                    $.each(linkArray, function(index, value) {
                        vlink = "[href='" + value + "']";
                        $('.form-textarea-wrapper iframe').contents().find(vlink).removeAttr("style");
                    });

                    $(this).text('Underperforming Link');
                })



                $('#chkul').change(function() {

                    if ($(this).is(":checked")) {

                        $.each(linkArray, function(index, value) {
                            vlink = "[href='" + value + "']";

                            $('.form-textarea-wrapper iframe').contents().find(vlink).css("border-bottom", "3px solid #f7b70c"); // orange
                        });


                    } else {

                        $.each(linkArray, function(index, value) {
                            vlink = "[href='" + value + "']";
                            $('.form-textarea-wrapper iframe').contents().find(vlink).removeAttr("style");
                        });

                    }
                });
                
                /*--------Paragraph Density--------------*/
    $("#chkpwd").change(function () {
        perParagraphHighlight(this, 'TOOSHORT', 'TOOLONG', PWDtooShortColor, PWDtooLongColor, PWDdomExpression, PWDparagraphs, 'pwd');
    });

    function perParagraphHighlight(element, stateA, stateB, colorA, colorB, domExpression, dataToHighlight, dimension)
    {
        if($(element).is(":checked")) {
            stateLabelA = stateA.toLowerCase().replace(' ', '-');
            stateLabelB = stateB.toLowerCase().replace(' ', '-');
            text_paragraphs = $('.form-textarea-wrapper iframe').contents().find(domExpression);
            $.each(dataToHighlight, function(index, value) {
                if (value == 'HIT' || value == 'UNAVAILABLE' || value == '' || value == 'length_hit')
                    return;
                type = (value == stateLabelA)?stateLabelA:stateLabelB;
                $(text_paragraphs[index]).wrapInner("<span class='highlight-"+dimension+" "+type+"'></span>");
            });
            $('.form-textarea-wrapper iframe').contents().find("."+stateLabelA).css("background", colorA);
            $('.form-textarea-wrapper iframe').contents().find("."+stateLabelB).css("background", colorB);
        }else{
            $('.form-textarea-wrapper iframe').contents().find(".highlight-"+dimension).contents().unwrap();
        }
    };


                // clear highlight before submiting form, this way will clean the html added to the iframe
                $('.node-form').submit(function( event ) {
                    $('.form-textarea-wrapper iframe').contents().find(".highlight-so").contents().unwrap();
                    $('.form-textarea-wrapper iframe').contents().find(".highlight-sp").removeAttr("style");
                    $('.form-textarea-wrapper iframe').contents().highlightRegex(undefined, {
                        tagType: 'span',
                        className: 'highlight-sp',
                    });
                    $('.form-textarea-wrapper iframe').contents().find(".highlight-grm").removeAttr("style");
                    $('.form-textarea-wrapper iframe').contents().highlightRegex(undefined, {
                        tagType: 'span',
                        className: 'highlight-grm',
                    });
                    $.each(linkArray, function(index, value) {
                        vlink = "[href='" + value + "']";
                        $('.form-textarea-wrapper iframe').contents().find(vlink).removeAttr("style");
                    });
                    return true;
                });

            });
//    });

            CustomDictionary = {
                add: function(w) {
                    return jQuery.ajax({
                        //url : 'sites/all/modules/atomicreach/inc/customDictionary.php',
                        data: {action: 'atomic_engager_custom_dictionary', word: w},
                        async: false
                    }).responseText == 'OK';
                }
            }
        }
    };
    
    /*
$('#chkpwd').change(function() {
   if($(this).is(':checked')) {
$( "#arTabContent > div" ).find( "label[for=chkpwd]" ).addClass('checked-label');
   }
});
$('label[for=chkso]').click(function() {
   if($(this).is(':checked')) {
$( "#arTabContent > div" ).find( "label[for=chkso]" ).addClass('checked-label');
   }
});
$('label[for=chksp]').click(function() {
   if($(this).is(':checked')) {
$( "#arTabContent > div" ).find( "label[for=chksp]" ).addClass('checked-label');
   }
});
$('label[for=chkgm]').click(function() {
   if($(this).is(':checked')) {
$( "#arTabContent > div" ).find( "label[for=chkgm]" ).addClass('checked-label');
   }
});

*/

})(jQuery);