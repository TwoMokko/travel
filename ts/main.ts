function NavigationTour(selector: string, top_absolute: number, top_fixed: number) {
	let $document = $(document);
	let $selector = $(selector);
	let $parent = $selector.parent();

	$document.on('scroll', Redraw);

	function Redraw(): void {
		let _top = $parent.offset().top;
		let _scroll = $document.scrollTop();

		if (_top + (top_absolute - top_fixed) <= _scroll) $selector.css({position: 'fixed', top: `${top_fixed}px`});
		else $selector.css({position: 'absolute', top: `${top_absolute}px`});
	}

	Redraw();
}

function ScrollTop(selector: string) {
	/*Elements*/
	let $document = $(document);
	let $elem = $(selector);
	let $button = $('<span/>', { class: 'arrow_top' });

	/*Building DOM*/
	$elem.append($button);

	/*Events*/
	$document.on('scroll', Redraw);
	$button.on('click', () => { $document.scrollTop(0); });

	function Redraw(): void {
		let _top = $elem.offset().top;
		let _scroll = $document.scrollTop();
		(_top < _scroll) ? $button.removeClass('hide') : $button.addClass('hide');
	}

	Redraw();
}