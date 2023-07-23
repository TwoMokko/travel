namespace Base {
	export namespace Skins {

		type TypeColumn = { alias: string, name: string, type: string };
		type TypeColumns = { [key: string]: TypeColumn };
		type TypeValue = { [key: string]: any };
		type TypeValues = TypeValue[];
		export class Table {
			number		: number;
			name		: string;
			columns		: TypeColumns;
			$container	: JQuery;
			$table		: JQuery;
			$thead		: JQuery;
			$tr_head	: JQuery;
			$tbody		: JQuery;
			$add		: JQuery;

			constructor(selector: string, name: string, columns: TypeColumns, values: TypeValues = []) {
				this.number = 0;
				this.name = name;
				this.columns = columns;
				this.$container = $(selector);
				this.$table = $('<table/>');
				this.$thead = $('<thead/>');
				this.$tbody = $('<tbody/>');
				this.$tr_head = $('<tr/>');
				this.$add = $('<input/>', {type: 'button', value: 'добавить'});

				this.$container.append(
					this.$table.append(
						this.$thead.append(this.$tr_head),
						this.$tbody
					),
					this.$add
				);

				for (let i in columns) this.$tr_head.append($('<td/>').text(columns[i].alias));
				this.$tr_head.append($('<td/>').text('удаление'));

				for (let i in values) this.AddColumn(values[i]);

				this.$add.on('click', this.AddColumn.bind(this));
			}
			private AddColumn(values: TypeValue = null) {
				this.number++;
				let tr = $('<tr/>');

				this.$tbody.append(tr);

				let $elem = $();
				for (let i in this.columns) {
					let value = values ? values[this.columns[i].name] : '';
					switch (this.columns[i].type) {
						case 'text': case 'number': $elem = this.GetInput(this.columns[i], this.number, value); break;
						case 'textarea': $elem = this.GetTextarea(this.columns[i], this.number, value); break;
					}
					tr.append($('<td/>').append($elem));
				}
				tr.append($('<td/>').append($('<input/>', {type: 'button', value: 'удалить' })).on('click', () => tr.remove() ));
			}

			private GetInput(params: TypeColumn, iter: number, value: string = ''): JQuery {
				return $('<input/>', {type: params.type, name: `${this.name}[${iter}][${params.name}]`, value: value});
			}

			private GetTextarea(params: TypeColumn, iter: number, value: string = ''): JQuery {
				return $('<textarea/>', {name: `${this.name}[${iter}][${params.name}]`, text: value});
			}

		}

		type TypePhotos = {[key: string] : { id: number, image: string }};

		export class UploaderPhoto {
			$wrap					: JQuery;
			$input					: JQuery;
			$space					: JQuery;
			$container				: JQuery;
			path_load				: string;
			path_del				: string;
			path_view				: string;

			constructor(selector: string, text: string, path_load: string, path_del: string, path_view: string, photos: TypePhotos) {
				this.$wrap 			= $('<div/>', {class: 'uploader_photo'});
				this.$input 		= $(selector);
				this.$space 		= $('<div/>', {class: 'upload_space'});
				this.$container 	= $('<div/>', {class: 'img_container'});
				this.path_load 		= path_load;
				this.path_del 		= path_del;
				this.path_view 		= path_view;

				this.$input.after(
					this.$wrap.append(
						this.$space.text(text),
						this.$container
					)
				);

				this.ShowFiles(photos);

				this.$wrap.prepend(this.$input);

				this.$input.on('change', (e) => {
					this.LoadFiles((e.target as HTMLInputElement).files);
					this.$input.val('');
				})
				this.$space.on('click', () => {
					this.$input.trigger('click');
				});

				this.$space.on('dragover', false);
				this.$space.on('dragenter', () => {
					this.$space.addClass('active');
				});
				this.$space.on('dragleave', () => {
					this.$space.removeClass('active');
				});
				this.$space.on('drop', e => {
					this.LoadFiles(e.originalEvent.dataTransfer.files);
					this.$space.removeClass('active');
					return false;
				});
			}

			private LoadFiles(files: FileList) {
				for (let i = 0; i < files.length; i++) {
					new File(files[i], this.$container, this.path_load, this.path_del);
				}
			}

			private ShowFiles(photos: TypePhotos) {
				for (let i in photos) {
					let $image = $('<div/>', {class: 'img'});
					let $del = $('<div/>', {class: 'delete active'});

					this.$container.append($image.append($del));
					$image.css('background-image', `url(${this.path_view}${photos[i].image})`);
					$del.on('click', () => {
						Base.Common.Query.SendData(this.path_del, {id: photos[i].id}, () => {
							$image.remove();
						}, {request: ''});
					});
				}
			}
		}

		class File {
			$image: JQuery;
			$del: JQuery;
			$wait: JQuery;

			constructor(file, $container: JQuery, path_load: string, path_del: string) {
				this.$image = $('<div/>', {class: 'img'});
				this.$del = $('<div/>', {class: 'delete'});
				this.$wait = $('<div/>', {class: 'wait active'});

				$container.append(
					this.$image.append(
						this.$wait,
						this.$del
					)
				);

				let reader = new FileReader();

				reader.onloadend = (e) => {
					this.$image.css('background-image', `url(${e.target.result})`);

					let data = new FormData();
					data.append('file', file);
					Base.Common.Query.SendData(path_load, data, data => {
						switch (data['action']) {
							case 'ok':
								this.$wait.removeClass('active');
								this.$del.addClass('active').on('click', () => {
									Base.Common.Query.SendData(path_del, data, () => {
										this.$image.remove();
									}, {request: ''});
								});
								break;
							case 'error': alert(data['text']);
						}
					}, {processData : false, contentType : false, request: ''});
				};


				reader.readAsDataURL(file);
			}
		}

	}
}