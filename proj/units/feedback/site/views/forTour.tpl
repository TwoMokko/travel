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
                            <input name = "name" type = "text" placeholder = "Имя*">
                        </div>
                        <div>
                            <input name = "contact" type = "text" placeholder = "Способ связи*">
                        </div>
                    </div>
                    <div>
                        <textarea name = "text" rows="5" placeholder = "Напишите сообщение или оставьте поле пустым"></textarea>
                    </div>
                    <div>
                        <a class = "button" onclick = "Base.Common.Query.SendForm($(this).closest('form'), AfterSend);">Оставить заявку</a>
                    </div>
                </form>
            </div>
        <?php }
    }




