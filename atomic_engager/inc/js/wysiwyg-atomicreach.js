(function($) {
    Drupal.behaviors.atomic_engager = {
        attach: function(context, settings) {
            $(document).ajaxComplete(function(e, xhr, settings) {

// Spelling Mistakes    
                aSm = $("ul.spelling-mistakes li").find('span.smText').clone().not(":last").append("\\b|\\b").end().text();
                var regexSm = new RegExp('(?:\\b|_)(' + aSm + ')(?:\\b|_)', 'ig');

//console.log(regexSm);

                $("#highlight-sp").toggle(function() {
                    $('.form-textarea-wrapper iframe').contents().highlightRegex(regexSm, {
                        tagType: 'span',
                        className: 'highlight-sp',
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
                            className: 'highlight-sp',
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
                aGm = $("ul.grammar-mistakes li").find('span.gmText').clone().not(":last").append("|").end().text();
                var regexGm = new RegExp(aGm, 'gi');

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
})(jQuery);