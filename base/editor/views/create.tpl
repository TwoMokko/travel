<?php

	namespace Base\Templates\Editor;

	use Base\Editor\Editor;
	use Base\Templates\Template;
	use Base\Templates\HTML\Element\Form;
	use Base\Templates\HTML\Element\Text;

	abstract class Create {

		public static function ToVar(Editor $editor, array $fields, array $data, string $title): string {
			Template::Start();
			self::Render($editor, $fields, $data, $title);
			return Template::Read();
		}

		public static function Render(Editor $editor, array $fields, array $data, string $title): void {
			$form = new Form($data);
		?>
			<div class = "navigate">
				<?php foreach ($editor->navigateCreate as $navigate) echo $navigate($editor->params); ?>
			</div>
			<h1><?= $title; ?></h1>
			<?php
				$form->Begin($editor->do_create->GetPath());
				foreach ($editor->params as $name => $params) Text::Render($name, $params, ['type' => 'hidden']);
				foreach ($fields as $field) if (get_class($field) == 'Base\Editor\Skins\Edit\Hidden') echo $field->ToVar();
			?>
			<table class = "create">
				<tbody>
					<?php foreach ($fields as $field) { if (get_class($field) == 'Base\Editor\Skins\Edit\Hidden') continue; ?>
						<tr>
							<th><?= $field->GetTitle(); ?>:</th>
							<td><?= $field->ToVar(); ?></td>
						</tr>
					<?php } ?>
				</tbody>
			</table>
			<?php $form->Submit('Создать', $editor->do_create->GetClick()); $form->End(); ?>
		<?php }

	}