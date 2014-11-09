'use strict';

// Declare app level module which depends on views, and components
var app = angular.module('ApiMock', ['ngRoute']).
    config(['$routeProvider', function($routeProvider) {
        $routeProvider.when("/", {
            templateUrl: "templates/overview.html",
            controller: "DashboardController"
        });
    }])
    .controller("DashboardController", ["$scope", function($scope) {
        $scope.apiList = [
            {
                endpoint: "/api/test1",
                desc: "First API" },
            {
                endpoint: "/api/test2",
                desc: "Second API" },
            {
                endpoint: "/api/test3",
                desc: "Third API"
            }
        ];


    }]);
