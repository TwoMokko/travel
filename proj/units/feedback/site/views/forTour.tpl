<?php

namespace Proj\Site\Templates\Feedback;

    use Base\Templates\Template;

    abstract class ForTour {

        public static function ToVar(): string
        {
            Template::Start();
            self::Render();
            return Template::Read();
        }

        public static function Render(): void { ?>
            <div class = "block tour_form">
                <div class = "header">Оставить заявку</div>
                <form action = "/feedback">
                    <div>
                        <div>
                            <input name = "name" type = "text" placeholder = "Имя*" minlength="3" maxlength="50">
                        </div>
                        <div>
                            <input name = "contact" type = "text" placeholder = "Способ связи*" minlength="3" maxlength="50">
                        </div>
                    </div>
                    <div>
                        <textarea name = "text" rows="5" placeholder = "Напишите сообщение или оставьте поле пустым" minlength="3" maxlength="255"></textarea>
                    </div>
                    <div>
                        <a class = "button" onclick = "if (Validation.Form($(this).closest('form'))) Base.Common.Query.SendForm($(this).closest('form'), AfterSend);">Оставить заявку</a>
<!--                        <a class = "button" onclick = "Base.Common.Query.SendForm($(this).closest('form'), AfterSend);">Оставить заявку</a>-->
                    </div>
                </form>
            </div>
        <?php }
    }




