<?php

namespace Proj\Site\Templates\Feedback;

    use Base\Templates\Template;
    use Proj\Site\Units\Feedback;
    use Proj\Site\Units\Tour;

    abstract class ForTour {

        public static function ToVar(int $id): string
        {
            Template::Start();
            self::Render($id);
            return Template::Read();
        }

        public static function Render(int $id): void { ?>
            <div class = "block tour_form">
                <div class = "header">Оставить заявку</div>
                <form action = "<?= Feedback::instance()->feedback->GetPath(); ?>">
                    <input name = "tour_id" type = "hidden" value = "<?= $id; ?>">
                    <div>
                        <div>
                            <input name = "name" type = "text" placeholder = "Имя*" minlength="3" maxlength="50">
                        </div>
                        <div>
                            <input name = "contact" type = "text" placeholder = "Способ связи*" minlength="3" maxlength="50">
                        </div>
                    </div>
                    <div>
                        <textarea name = "text" rows="5" placeholder = "Напишите сообщение или оставьте поле пустым" maxlength="255"></textarea>
                    </div>
                    <div>
                        <a class = "button" onclick = "if (Validation.Form($(this).closest('form'))) Base.Common.Query.SendForm($(this).closest('form'), AfterSend);">Оставить заявку</a>
<!--                        <a class = "button" onclick = "Base.Common.Query.SendForm($(this).closest('form'), AfterSend);">Оставить заявку</a>-->
                    </div>
                </form>
            </div>
        <?php }
    }




