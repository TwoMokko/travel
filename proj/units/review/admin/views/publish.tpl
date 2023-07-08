<?php

	namespace Proj\Admin\Templates\Reviews;

	use Proj\Admin\Editor;
	use Base\Templates\Template;
	use Base\Templates\HTML\Element\Form;
	use Base\Templates\HTML\Element\Text;

	abstract class Publish {

		public static function ToVar(Editor\Reviews $editor, int $id, array $fields, array $item, array $data, string $title): string {
			Template::Start();
			self::Render($editor, $id, $fields, $item, $data, $title);
			return Template::Read();
		}

		public static function Render(Editor\Reviews $editor, int $id, array $fields, array $item, array $data, string $title): void {
            $form = new Form($data);
        ?>
            <div class = "navigate">
                <?php foreach ($editor->navigateUpdate as $navigate) echo $navigate($editor->params); ?>
            </div>
            <h1><?= $title; ?></h1>
        <?php
            $form->Begin($editor->do_publish->GetPath());
            Text::Render('id', $id, ['type' => 'hidden']);
        ?>
            <table class = "update">
                <tbody>
                    <tr>
                        <th><?= $fields['tour_id']->GetTitle(); ?>:</th>
                        <td><?= $fields['tour_id']->ToVar($item['gid']); ?></td>
                    </tr>
                    <tr>
                        <th><?= $fields['name']->GetTitle(); ?>:</th>
                        <td><?= $fields['name']->ToVar($item['name']); ?></td>
                    </tr>
                    <tr>
                        <th><?= $fields['text']->GetTitle(); ?>:</th>
                        <td><?= $fields['text']->ToVar($item['text']); ?></td>
                    </tr>
                    <tr>
                        <th>Аватарка:</th>
                        <td><?= ''; ?></td>
                    </tr>
                </tbody>
            </table>
        <?php
            $form->Submit('Опубликовать', $editor->do_update->GetClick()); $form->End();
        }

	}