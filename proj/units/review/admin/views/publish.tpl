<?php

	namespace Proj\Admin\Templates\Reviews;

	use Base\Editor\Editor;
	use Base\Templates\Template;
	use Base\Templates\HTML\Element\Form;
	use Base\Templates\HTML\Element\Text;

	abstract class Publish {

		public static function ToVar(Editor $editor, array $fields, int $id, array $item, string $title, array $navigate, array $params): string {
			Template::Start();
			self::Render($editor, $fields, $id, $item, $title, $navigate, $params);
			return Template::Read();
		}

		public static function Render(Editor $editor, array $fields, int $id, array $item, string $title, array $navigate, array $params): void {
            $form = new Form($data);
        ?>
            <div class = "navigate">
				<?php foreach ($navigate as $func) echo $func(); ?>
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