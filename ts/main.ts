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