jQuery('document').ready( function () {
    var map = L.map('map', {
       center: [25,7],
       zoom: 2
     });


L.tileLayer('https://api.tiles.mapbox.com/v4/shared-ea-account.ee9fbb54/{z}/{x}/{y}.png?access_token=pk.eyJ1Ijoic2hhcmVkLWVhLWFjY291bnQiLCJhIjoiM2M3YjdmNzcwNDg1MmM5YjliMzIyNThkZTc2OWJjMWUifQ.-QAdcCLKxJZr8dtAofvdsw',{
       maxZoom: 18,
       attribution: 'Map data &copy; <a href="http://openstreetmap.org">OpenStreetMap</a> contributors, ' +
		            '<a href="http://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, ' +
		            'Imagery &copy <a href="http://mapbox.com">Mapbox</a>'
     }).addTo(map);


     var markerData = window.markerData;
     var markers = new L.MarkerClusterGroup({maxClusterRadius: 60});
     for(var i = 0; i < markerData.length; i++) {
       var currentMarkerData = markerData[i];
       var latlng = currentMarkerData.latlng;
       var popup = currentMarkerData.popup;
       var marker = new L.marker(latlng).bindPopup(popup);
       markers.addLayer(marker);
     }

     // add groups
     var groups = window.groups;
     for(var i = 0; i < groups.length; i++) {
       var currentMarkerData = groups[i];
       var latlng = currentMarkerData.latlng;
       var popup = currentMarkerData.popup;
       var marker = new L.marker(latlng, {icon: L.AwesomeMarkers.icon({icon: 'users', markerColor: 'orange', prefix: 'fa', iconColor: 'black'}) }).bindPopup(popup);
       markers.addLayer(marker);
     }

     map.addLayer(markers);
}
);
