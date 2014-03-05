RoomDraw = {
	
};
// Load required data from server
var HOST = "127.0.0.1";
var roomData;
var brothers;  
// Load room capacity configuration
d3.csv("http://"+HOST+":9000/roomconfig.csv", function(data) {
	roomData = data;
});
// Load points list - we now know the points.
d3.csv("http://"+HOST+":9000/points.csv", function(d) {
	brothers = d;
});

function roomClick() {

}


var rooms = d3.select("body").select("svg").select("g#layer1").select("g#rooms").selectAll("g");
rooms.selectAll("rect").style("fill", "lightgray");
rooms.selectAll("rect").style("opacity", "0.75");
rooms.on("mouseover", function() {
	d3.select(this).selectAll("rect").transition().style("fill", "red");
});
rooms.on("mouseout", function() {
	d3.select(this).selectAll("rect").transition().style("fill", "lightgray");
});