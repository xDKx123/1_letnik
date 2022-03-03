const server = 'http://localhost:6060';

const getTodoListsRoute = '/getTodoLists';
const updateTodoListRoute = '/updateTodoList';
const deleteTodoListRoute = '/deleteTodoList';
const addTodoListRoute = '/addTodoList';

const getTodoListItemsRoute = '/getTodoListItems';
const updateTodoListItemRoute = '/updateTodoListItem';
const deleteTodoListItemRoute = '/deleteTodoListItem';
const addTodoListItemRoute = '/addTodoListItem';

const getTagsRoute = '/getTags';
const updateTagRoute = '/updateTag';
const deleteTagRoute = '/deleteTag';
const addTagRoute = '/addTag';


let activeListName = "";

$(document).ready(function() {
    getTodoLists();

    // Get the modal
    var editFormTodoList = document.getElementById("editFormTodoList");
    var editFormTodoListItem = document.getElementById("editFormTodoListItem");
    var editFormTag = document.getElementById("editFormTag");

    // Get the button that opens the modal
    var btn = document.getElementById("updateTodoList");

    // Get the <span> element that closes the modal
    //var span = document.getElementsByClassName("close")[0];

    // When the user clicks on the button, open the modal
    btn.onclick = function() {
        editFormTodoList.style.display = "block";
    }

    // When the user clicks on <span> (x), close the modal
    //span.onclick = function() {
    //modal.style.display = "none";
    //}

    // When the user clicks anywhere outside of the modal, close it
    window.onclick = function(event) {
        if (event.target == editFormTodoList) {
            editFormTodoList.style.display = "none";
        }
        else if (event.target == editFormTodoListItem) {
            editFormTodoListItem.style.display = "none";
        }
        else if (event.target == editFormTag) {
            editFormTag.style.display = "none";
        }
    }
});


function newTodoItem() {
    document.getElementById("fieldsNewTodoListNotAssigned").textContent = "";
    let name = document.getElementById("inputTodoListId").value;

    if (!name || name == '') {
        document.getElementById("fieldsNewTodoListNotAssigned").textContent="Insert a unique name";
        return;
    }

    $.post({
        url: server + addTodoListRoute,
        data: {"name": name},
        success: function (data, textStatus, xhr) {

            if(textStatus === 'success'){
                if (data.success == true) {
                    getTodoLists();
                }
                else {
                    alert("Insert failed");
                }

            }
        },
        error: function (xhr, error_text, statusText) {
            alert("Error adding list");
            console.log(xhr.code, xhr);  // there returns the status code
        }

    });

    document.getElementById("inputTodoListId").value = "";

}

function getTodoLists() {
    $.post({
        url: server + getTodoListsRoute,
        success: function (data, textStatus, xhr) {

            if(textStatus === 'success'){
                console.log(Array.from(data.message).length);

                let arr = Array.from(data.message);

                let text = "<ul>";
                for (let x = 0; x < arr.length; x++) {

                    if (x == 0) {
                        activeListName = arr[x].name;
                        getTodoListItems(arr[x].id, activeListName);
                    }

                    text+='<li><button id="todoItem" '+ arr[x].id + 'type="button" class="btn btn-link" onclick="getTodoListItems(' + arr[x].id +', ' + '\'' + arr[x].name + '\'' + ')">' + arr[x].name + '</button></li>';
                    
                }
                text += "</ul>";

                let element = document.getElementById("todoLists");
                element.innerHTML = text;
            }
        },
        error: function (xhr, error_text, statusText) {
            alert("Error getting lists");
            console.log(xhr.code, xhr);  // there returns the status code
        }

    });
}

function getTodoListItems(id, nameTodoList) {
    activeListName = nameTodoList;

    $.post({
        url: server + getTodoListItemsRoute,
        data: {"todoListId": id},
        success: function (data, textStatus, xhr) {

            if(textStatus === 'success'){
                console.log(data);   // there returns the status code

                let arr = Array.from(data.message);

                let text = "";
                for (let x = 0; x < arr.length; x++) {

                    let date = (moment(new Date(arr[x].end_date))).format('YYYY-MM-DDThh:mm');

                    let color = '';

                    if (moment(date).isBefore(new Date())) {
                        color+='red;"';
                    }
                    else if (moment(date).subtract(parseInt(arr[x].reminder_days), 'days').isBefore(new Date())) {
                        color+='orange;"';
                    }
                    else {
                        color+='black;"';
                    }


                    var tagsHtml = '<div id="tagsList_' + arr[x].id +'">';

                    tagsHtml += "</div>";
                    console.log(tagsHtml);
                    debugger;

                    text+= '<div class="row" style="border: 1px solid grey; border-radius: 16px; margin-bottom: 5px;"><div class="col-2"><button class="btn" style="cursor: pointer" onclick="removeTodoListItem(' + arr[x].id + "," + id + ", \'" + nameTodoList + '\'' + ')"><span class="glyphicon glyphicon-remove" style="font-size: 3em;"></span></button><button class="btn" onclick="editTodoListForm(' + arr[x].id +', \'' + arr[x].name + '\', \'' + arr[x].end_date + '\', ' + arr[x].reminder_days + ', ' + id + ' )" style="cursor: pointer"><span class="glyphicon glyphicon-edit" style="font-size: 3em"></button></div><div class="col-5"><h3 style="color: '+ color +'">' + arr[x].name +'</h3></div><div class="col-3"><p>'+ arr[x].end_date +'</p></div><div class="col-2"><button class="btn" onclick="addTag(' + arr[x].id + ', ' + id + ')">Add tag</button>' + tagsHtml + '</div></div>';
                }

                let element = document.getElementById("todoListItems");
                element.innerHTML = text;

                for (let x = 0; x < arr.length; x++) {
                    getTags(arr[x].id, function (tagsArray) {
                        let tagsHtmlItem = document.getElementById("tagsList_" + arr[x].id);
                        let tagsHtml = "";
                        for (var y = 0; y < tagsArray.length; y++) {
                            tagsHtml += '<div id="tag_' + tagsArray[y].id + '" style="display: flex; align-items: baseline"><p id="tag_p_' + tagsArray[y].id + '">' + tagsArray[y].name + '</p>';

                            tagsHtml += '<button id="updateTag" class="btn btn-outline-secondary" onclick="updateTagEditForm(' + tagsArray[y].id + ', ' + id + ');return false;"><span class="fa fa-edit"></span></button>';
                            tagsHtml += '<button id="removeTag" class="btn btn-outline-secondary" onclick="deleteTag(' + tagsArray[y].id + ', ' + id + ');return false;"><span class="fa fa-remove"></span></button>';

                            tagsHtml += '</div>';
                        }
                        tagsHtmlItem.innerHTML = tagsHtml;
                    });
                }

                // let btn = document.getElementById("newTodoItem");
                // btn.setAttribute('onclick',  'newTodoItem(' + id + ');return false');

                $("#newTodoListItemButton").removeAttr("onclick");
                $("#newTodoListItemButton").attr("onclick", 'newTodoListItem(' + id + ');return false');

                $("#updateTodoListButton").removeAttr("onclick");
                $("#updateTodoListButton").attr("onclick", 'updateTodoList(' + id + ');return false');

                document.getElementById("headerTodoList").innerHTML = nameTodoList;

                $("#removeTodoList").removeAttr("onclick");
                $("#removeTodoList").attr("onclick", 'deleteTodoList(' + id + ');return false');
            }
        },
        error: function (xhr, error_text, statusText) {
            alert("Error getting items");
            console.log(xhr.code, xhr);  // there returns the status code
        }

    });
}

function removeTodoListItem(id_item, id_list, nameList) {
    $.post({
        url: server + deleteTodoListItemRoute,
        data: {"todoListItemId": id_item},
        success: function (data, textStatus, xhr) {

            if(textStatus === 'success'){
                console.log(data);   // there returns the status code


                getTodoListItems(id_list, nameList);
            }
        },
        error: function (xhr, error_text, statusText) {
            alert("Error removing item");
            console.log(xhr.code, xhr);  // there returns the status code
        }

    });
}


function newTodoListItem(listId) {
    document.getElementById("fieldsNewTodoItemNotAssigned").textContent="";

    let name = document.getElementById("addTodoListItemName").value;
    let endDate = document.getElementById("end_date").value;
    //let reminderDate = document.getElementById("reminder_date").value;
    let reminderDate = document.getElementById("reminder_date").value;

    if (!name || name == '') {
        document.getElementById("fieldsNewTodoItemNotAssigned").textContent="Please fill all fields";
        return;
    }
    
    let endDateFormat = null;
    //let reminderDateFormat = null;

    if (endDate) {
        endDateFormat = (moment(new Date(endDate))).format('YYYY-MM-DD');
    }
    if (!reminderDate) {
        reminderDate = 0;
    }

    $.post({
        url: server + addTodoListItemRoute,
        data: {"name": name, "end_date": endDateFormat, "reminder_date": reminderDate, "todoListId": listId},
        success: function (data, textStatus, xhr) {

            if(textStatus === 'success'){
                if (data.success == true) {
                    getTodoListItems(listId, activeListName);
                }
                else {
                    alert("Insert failed");
                }

            }
        },
        error: function (xhr, error_text, statusText) {
            alert("Error adding item");
            console.log(xhr.code, xhr);  // there returns the status code
        }

    });

    document.getElementById("addTodoListItemName").value = "";
    document.getElementById("end_date").value = "";
    document.getElementById("reminder_date").value = "";

}

function updateTodoList(id) {
    let newName = document.getElementById("newTodoListName").value;

    $.post({
        url: server + updateTodoListRoute,
        data: {"name": newName, "id": id},
        success: function (data, textStatus, xhr) {

            if(textStatus === 'success'){
                if (data.success == true) {
                    var modal = document.getElementById("editFormTodoList");
                    modal.style.display = "none";

                    getTodoLists();
                    getTodoListItems(id, activeListName);


                }
                else {
                    alert("Update failed");
                }

            }
        },
        error: function (xhr, error_text, statusText) {
            alert("Error updating list");
            console.log(xhr.code, xhr);  // there returns the status code
        }

    });
}

function deleteTodoList(id) {
    $.post({
        url: server + deleteTodoListRoute,
        data: {"todoListId": id},
        success: function (data, textStatus, xhr) {

            if(textStatus === 'success'){

                getTodoLists();
                getTodoListItems(id, activeListName);
            }
        },
        error: function (xhr, error_text, statusText) {
            alert("Error deleting list");
            console.log(xhr.code, xhr);  // there returns the status code
        }

    });
}

function getTags(listItemId, callback) {

    $.post({
        url: server + getTagsRoute,
        data: {"listItemId": listItemId},
        success: function (data, textStatus, xhr) {

            if(textStatus === 'success'){

                callback(Array.from(data.message));

            }
        },
        error: function (xhr, error_text, statusText) {
            debugger;
            callback([]);

            alert("Error getting tags");
            console.log(xhr.code, xhr);  // there returns the status code
        }

    });
}

function updateTag(id, listId) {
    let newTagName = document.getElementById("newTagName").value;

    $.post({
        url: server + updateTagRoute,
        data: {"id": id, "name": newTagName},
        success: function (data, textStatus, xhr) {

            if(textStatus === 'success'){
                document.getElementById("editFormTag").style.display = "none";

                getTodoListItems(listId, activeListName);
            }
        },
        error: function (xhr, error_text, statusText) {
            alert("Error updating tag");
            console.log(xhr.code, xhr);  // there returns the status code
        }

    });
}

function deleteTag(id, listId) {
    $.post({
        url: server + deleteTagRoute,
        data: {"id": id},
        success: function (data, textStatus, xhr) {

            if(textStatus === 'success'){

                getTodoListItems(listId, activeListName);
            }
        },
        error: function (xhr, error_text, statusText) {
            alert("Error deleting tag");
            console.log(xhr.code, xhr);  // there returns the status code
        }

    });
}

function addTag(listItemId, listId) {
    $.post({
        url: server + addTagRoute,
        data: {"todoListItemId": listItemId, "name": "newTag"},
        success: function (data, textStatus, xhr) {

            if(textStatus === 'success'){

                getTodoListItems(listId, activeListName);
            }
        },
        error: function (xhr, error_text, statusText) {
            alert("Error adding tag");
            console.log(xhr.code, xhr);  // there returns the status code
        }

    });
}

function updateTagEditForm(id, listId) {
    $("#updateTagButton").removeAttr("onclick");
    $("#updateTagButton").attr("onclick", 'updateTag(' + id + ', ' + listId + ')');


    var editFormTag = document.getElementById("editFormTag");
    editFormTag.style.display = "block";
}

function editTodoListForm(id, name, end_date, reminder_days, listId) {
    var editFormTodoListItem = document.getElementById("editFormTodoListItem");
    editFormTodoListItem.style.display = "block";

    document.getElementById("newTodoListItemName").value = name;

    console.log(new Date(end_date));
    document.getElementById("newTodoListItemDate").value = (moment(new Date(end_date))).format('YYYY-MM-DDThh:mm');

    document.getElementById("newTodoListItemReminder").value = reminder_days;

    $("#updateTodoListItemButton").removeAttr("onclick");
    $("#updateTodoListItemButton").attr("onclick", 'updateTodoListItem(' + id + ', ' + listId + ')');
}

function updateTodoListItem(id, listId) {
    let name = document.getElementById("newTodoListItemName").value;
    let end_date = document.getElementById("newTodoListItemDate").value;
    let reminder_days = document.getElementById("newTodoListItemReminder").value;

    let endDateFormat = null;
    if (end_date) {
        endDateFormat = (moment(new Date(end_date))).format('YYYY-MM-DD');
    }
    if (!reminder_days) {
        reminder_days = 0;
    }

    $.post({
        url: server + updateTodoListItemRoute,
        data: {"id": id, "name": name, "end_date": endDateFormat, "reminder_days": reminder_days},
        success: function (data, textStatus, xhr) {

            if(textStatus === 'success'){


                getTodoListItems(listId, activeListName);
            }
        },
        error: function (xhr, error_text, statusText) {
            alert("Error adding tag");
            console.log(xhr.code, xhr);  // there returns the status code
        }

    });

    var editFormTodoListItem = document.getElementById("editFormTodoListItem");
    editFormTodoListItem.style.display = "none";
}