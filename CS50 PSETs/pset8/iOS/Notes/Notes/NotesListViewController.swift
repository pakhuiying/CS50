import UIKit

class NotesListViewController: UITableViewController {
    
    var notes: [Note] = []
    
    @IBAction func createNote() {
        let _ = NoteManager.shared.create()
        reload()
    }
    
    func reload() {
        notes = NoteManager.shared.getNotes()
        tableView.reloadData()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        reload()
    }
    
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return notes.count
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "NoteCell", for: indexPath)
        cell.textLabel?.text = notes[indexPath.row].content
        return cell
    }
    
    /*override func tableView(_ tableView: UITableView, editActionsForRowAt indexPath: IndexPath) -> [UITableViewRowAction]? {
        let delete = UITableViewRowAction(style: .destructive, title: "Delete") {(action, indexPath) in self.notes.remove(at: indexPath.row)
            self.tableView.deleteRows(at: [indexPath], with: .fade)
            //NoteManager.shared.deleteNotes(id: Int(indexPath.row))
            
            //self.notes[indexPath.row].id =
            //slide to delete rows
        }
        NoteManager.shared.deleteNotes(note: self.notes[indexPath.row])
        print("deleted id: \(self.notes[indexPath.row].id)")
       // print("deleted indexPath.row: \(indexPath.row)")
        //print("index path: \([indexPath])")
        reload()
        return [delete]
    }*/
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCell.EditingStyle, forRowAt indexPath: IndexPath) {
        if editingStyle == .delete {
            NoteManager.shared.deleteNotes(note: self.notes[indexPath.row])
            notes.remove(at: indexPath.row)
            tableView.deleteRows(at: [indexPath], with: .fade)
        } else if editingStyle == .insert {
            // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
        }
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "NoteSegue",
                let destination = segue.destination as? NoteViewController,
                let index = tableView.indexPathForSelectedRow?.row {
            destination.note = notes[index]
        }
    }
}
