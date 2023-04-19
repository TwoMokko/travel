type TypePhotos = {[key: string] : { id: number, image: string }};

namespace Functions {
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
			console.log(photos);
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
					this.$wait.removeClass('active');
					this.$del.addClass('active').on('click', () => {
						Base.Common.Query.SendData(path_del, data, () => {
							this.$image.remove();
						}, {request: ''});
					});
				}, {processData : false, contentType : false, request: ''});
			};


			reader.readAsDataURL(file);
		}
	}
}

	// <div class = "uploader_photo">
	// <input type = "<?= $this->type; ?>" name = "<?= $this->name; ?>" <?= $accept; ?> onchange = "Functions.UploaderPhoto();" multiple>
	// <div class = "upload_space">
	// <div class = "background_text">Нажмите для загрузки или перетащите сюда</div>
	// </div>
	// <div class = "img_container">
	// <div class = "img">
	// <div class = "delete"></div>
	// 	</div>
	// 	</div>
	// 	</div>


	// export function UploaderPhoto(): void {
	// 	console.log('123');
	// }
	//
	// export function OnDrop(e) {
	// 	console.log(e);
	// 	e.preventDefault();
	// }
	//
	// export function X(selector) {
	// 	let $uploader = $(selector);
	// 	let $space = $uploader.children('.upload_space');
	//
	// 	$space.on('dragover', false);
	// 	$spase.
	// 	$space.on('drop', function(e) {
	// 		console.log(e);
	// 		console.log('1');
	// 		e.preventDefault();
	// 		e.stopPropagation();
	// 		return false;
	// 	});
	//
	// }

