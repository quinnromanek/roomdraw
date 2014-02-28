RoomDraw = {
	
};


function roomClick() {

}


var rooms = d3.select("body").select("svg").select("g#layer1").select("g#rooms").selectAll("g");
rooms.selectAll("rect").style("fill", "yellow");
rooms.selectAll("rect").style("opacity", "0.75");
rooms.on("mouseover", function() {
	d3.select(this).selectAll("rect").transition().style("fill", "blue");
});
rooms.on("mouseout", function() {
	d3.select(this).selectAll("rect").transition().style("fill", "yellow");
})