'use strict';

// Declare app level module which depends on views, and components
var app = angular.module('ApiMock', ['ngRoute', 'ui.bootstrap', 'ui.codemirror']).
    config(['$routeProvider', function($routeProvider) {
        $routeProvider.when("/", {
            templateUrl: "templates/overview.html",
            controller: "DashboardController"
        }).when("/endpoints", {
            templateUrl: "templates/endpoints.html",
            controller: "DashboardController"
        });
    }])

    .factory("ApiService", [
        "$http", function($http) {
            var apiList = [
                {
                    apiId: 1,
                    endpoint: "/api/test1",
                    desc: "First API",
                    resources: [
                        { uri: "/user" },
                        { uri: "/user/{id}" },
                        { uri: "/user/{id}/friends" },
                        { uri: "/offers/{date}" }
                    ]},
                {
                    apiId: 2,
                    endpoint: "/api/test2",
                    desc: "Second API",
                    resources: [
                        { uri: "/cats" },
                        { uri: "/dogs" },
                        { uri: "/dogs/{id}" },
                        { uri: "/cats/{id}" }
                    ]},
                {
                    apiId: 3,
                    endpoint: "/api/test3",
                    desc: "Third API",
                    resources: [
                        { uri: "/customer" },
                        { uri: "/sales" },
                        { uri: "/customer/{id}" },
                        { uri: "/customer/{id}/orders" }
                    ]
                }
            ];

            var subscribers = [];

            var notify = function (onNotify) {
                subscribers.forEach(onNotify);
            };

            var notifyApiListChanged = function (subscriber) {
                subscriber.onApiListChanged(angular.copy(apiList));
            }

            return {
                subscribe: function(s) {
                    subscribers.push(s);
                    notifyApiListChanged(s);
                }
            };
        }])

    .controller("DashboardController", ["$scope", "$modal", "ApiService", function($scope, $modal, ApiService) {
        $scope.apiList = [];

        $scope.selectAppropriateItem = function () {
            if (!$scope.currentApi && $scope.apiList.length > 0)
                $scope.currentApi = $scope.apiList[0];
        };

        $scope.onApiListChanged = function(list) {
            $scope.apiList = list;
            $scope.selectAppropriateItem();
        };

        ApiService.subscribe($scope);

        $scope.open = function () {
            $modal.open({
                templateUrl: "templates/addroute.html",
                controller: "RouteEditController"
            });
        };
    }])

    .controller("LocationController", ["$scope", "$location", function($scope, $location) {
       $scope.isActive = function(url) {
           return $location.path() == url;
       }
    }])

    .controller("RouteEditController", ["$scope", "ApiService", function($scope, ApiService) {
        $scope.editorOptions = {
            value: "x",
            lineWrapping: true,
            lineNumbers: true,
            styleActiveLine: true,
            autofocus: true,
            matchBrackets: true,
            autoCloseBrackets: true,
            theme: "neat"
        };

        $scope.code = "var x = 0;";
    }]);
