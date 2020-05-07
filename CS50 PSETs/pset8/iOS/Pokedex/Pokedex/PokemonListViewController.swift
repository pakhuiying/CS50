import UIKit
//view the list of pokemons
class PokemonListViewController: UITableViewController, UISearchBarDelegate {
    //create an empty list that holds a type of struct PokemonListResult
    var pokemon: [PokemonListResult] = []
    @IBOutlet var searchpokemon: UISearchBar!
    
    func capitalize(text: String) -> String {
        return text.prefix(1).uppercased() + text.dropFirst()
    } //create function to capitalise first letter
    
    var filteredPokemon: [PokemonListResult]!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        tableView.dataSource = self
        searchpokemon.delegate = self //delegate search bar to viewDidLoad
        /*store the result of search in another class variable whose type is a list of PokemonListResult*/
        filteredPokemon = pokemon
        
        guard let url = URL(string: "https://pokeapi.co/api/v2/pokemon?limit=151") else {
            return
        }
        
        URLSession.shared.dataTask(with: url) { (data, response, error) in
            guard let data = data else {
                return
            }
            
            do {
                let entries = try JSONDecoder().decode(PokemonListResults.self, from: data)
                self.pokemon = entries.results //populate pokemon list with results
                DispatchQueue.main.async {
                    self.tableView.reloadData()//update pokemon list
                }
            }
            catch let error {
                print(error)
            }
        }.resume()
    }
    
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "PokemonCell", for: indexPath)
        cell.textLabel?.text = capitalize(text: filteredPokemon[indexPath.row].name)
        return cell
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        //return pokemon.count
        
        return filteredPokemon.count
        
        //number of rows in table = number of pokemon
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        //seque is a way of transitioning between interfaces
        if segue.identifier == "ShowPokemonSegue",
            //when u click on a row it should link to next page->PokemonViewController
                let destination = segue.destination as? PokemonViewController,
            //index of pokemon will correspond to the row number
                let index = tableView.indexPathForSelectedRow?.row {
            destination.url = filteredPokemon[index].url
        }
    }
    
    func searchBar(_ searchBar: UISearchBar, textDidChange searchText: String) {
        //this searchBar func tells the delegate that the user changed the search text
        //textDidChange is a type.
        //searchText is the current text in the search text field
        //if search bar is empty, filterpokemon = pokemon'
        /*if searchText == "" {
            filteredPokemon = pokemon
            tableView.reloadData()
            return
        }*/
        
        filteredPokemon = searchText.isEmpty ? pokemon : pokemon.filter{(pokemon: PokemonListResult) -> Bool in return pokemon.name.lowercased().contains(searchText.lowercased())
            
        }
        
        

        
        tableView.reloadData()
    }
}

